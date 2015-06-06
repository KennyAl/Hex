// Fill out your copyright notice in the Description page of Project Settings.

#include "Hex.h"
#include "EditorRenderComponent.h"


// Sets default values for this component's properties
UEditorRenderComponent::UEditorRenderComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = false;
	PrimaryComponentTick.bCanEverTick = false;
	Inst.Add(ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("Bla")));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMesh>(this, TEXT("Mesh"));

	bIsInitialized = false;
	RenderMode = ERenderMode::ENone;
	bCastShadows = true;
	Scale.Set(1.0f, 1.0f);
}


// Called when the game starts
void UEditorRenderComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
}

void UEditorRenderComponent::TEST_DynamicComps()
{
	//Inst.Add(ConstructObject<UInstancedStaticMeshComponent>(UInstancedStaticMeshComponent::StaticClass()->GetClass()/*, this, TEXT(" %d"), Inst.Num()*/));
	Inst.Add(NewNamedObject<UInstancedStaticMeshComponent>(this, TEXT(" %d")/*, Inst.Num()*/));
	FName NewName(TEXT("%d"), Inst.Num());
	Inst[1]->RegisterComponent();
	Inst[1]->StaticMesh = Mesh;
	FTransform Trans(FRotator(0), FVector(0));
	Inst[1]->AddInstanceWorldSpace(Trans);
}

void UEditorRenderComponent::Init(UMapDataset* NewMapData)
{
	if (bIsInitialized)
	{
		UE_LOG(Editor, Warning, TEXT("Component is already initialized, abording ..."));
		return;
	}

	// Set the map data
	if (!NewMapData)
	{
		UE_LOG(Editor, Warning, TEXT("MapData is null"));
		return;
	}
	else
	{
		MapData = NewMapData;
	}
	
	// Check the altitude visuals
	if (AltitudeMeshes.Num() != AltitudeMaterials.Num())
	{
		UE_LOG(Editor, Warning, TEXT("Altitude meshes and materials count do not match"));
	}

	for (int32 Mat = 0; Mat < AltitudeMaterials.Num(); Mat++)
	{
		if (!AltitudeMaterials[Mat]->bUsedWithInstancedStaticMeshes)
		{
			UE_LOG(Editor, Warning, TEXT("Materials can not be used with instanced meshes. Index: %d"), Mat);
		}
	}

	// If there is at least one mesh available, calculate the dimensions for future use
	if (AltitudeMeshes.Num() > 0)
	{
		// Because of the reversed axis in the game, we need to reverse this here as well
		FBoxSphereBounds MeshBounds = AltitudeMeshes[0]->GetBounds();
		TileMeshDim.X = MeshBounds.BoxExtent.Y * 2;
		TileMeshDim.Y = MeshBounds.BoxExtent.X * 2;
	}
	else
	{
		UE_LOG(Editor, Warning, TEXT("No altitude meshes or materials are availalbe"));
	}

	bIsInitialized = true;
}

void UEditorRenderComponent::SwitchRenderMode(ERenderMode NewRenderMode)
{
	ERenderMode OldRenderMode = RenderMode;
	RenderMode = NewRenderMode;
	if (RedrawMap())
	{
		UE_LOG(Editor, Warning, TEXT("Can't redraw the map"));
		RenderMode = OldRenderMode;
	}
}

bool UEditorRenderComponent::RedrawMap()
{
	// Abort if the render component is not initialized
	if (!bIsInitialized)
	{
		UE_LOG(Editor, Warning, TEXT("Render component is not initialized"));
		return false;
	}
	
	switch (RenderMode)
	{
	case ERenderMode::ENone:
		ClearMap();
		// We don't have to draw anything new if the render mode is set to "None"
		UE_LOG(Editor, Warning, TEXT("Render mode is set to 'None', clearing map and returning"));
		break;

	case ERenderMode::ELandMass:
		ClearMap();
		// After checking if the enough meshes are available, set up two instanced mesh components
		// One for water (-1) and one for land (0)
		if (AltitudeMeshes.IsValidIndex(WaterLevelIndex - 1) && AltitudeMeshes.IsValidIndex(WaterLevelIndex))
		{
			for (int32 CurrentAltitude = WaterLevelIndex - 1; CurrentAltitude <= WaterLevelIndex; CurrentAltitude++)
			{
				FName NewName(TEXT("%d"), MeshComponents.Num());
				int32 NewIndex = MeshComponents.Add(NewNamedObject<UInstancedStaticMeshComponent>(this, NewName));
				MeshComponents[NewIndex]->RegisterComponent();
				MeshComponents[NewIndex]->StaticMesh = AltitudeMeshes[CurrentAltitude];
				MeshComponents[NewIndex]->SetMaterial(0, AltitudeMaterials[CurrentAltitude]);
				MeshComponents[NewIndex]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				// CastShadow is a bitflag, but this will work as well
				MeshComponents[NewIndex]->CastShadow = bCastShadows;
			}
		}
		else
		{
			UE_LOG(Editor, Warning, TEXT("Not enough meshes available for drawing of the landmass"));
			return false;
		}

		// For some odd reason the compiler gives an error because "the initialization of Loc and Trans
		// is skipped by the cases below"
		// However it works just fine while nested inside another block
		{
			FTransform Trans(FRotator(0), FVector(0), FVector(Scale.X, Scale.X, Scale.Y));
			FVector Loc(0);
			// Calculate the needed offset on the x axis in world space which resolves to:
			// Half of the mesh width multiplied by the tan of one angle of the hexagon (30°)
			float Offset = TileMeshDim.X / 2 * FMath::Tan(FMath::DegreesToRadians(30));
			
			// Now we just need to loop through the map data and add instances according to the tile information
			bool Shifted = false;
			for (int32 Y = 0; Y < MapData->GetSize()->Y; Y++)
			{
				Loc.X = (Y * TileMeshDim.Y - Offset * Y) * Scale.X;
				for (int32 X = 0; X < MapData->GetSize()->X; X++)
				{
					Loc.Y = X * TileMeshDim.X * Scale.X;
					// Every second row is shifted to the right by half of the tile width
					if (Shifted)
					{
						Loc.Y += TileMeshDim.X / 2 * Scale.X;
					}
					Trans.SetLocation(Loc);
					if (MapData->GetTile(X, Y).IsLand)
					{
						MeshComponents[1]->AddInstanceWorldSpace(Trans);
					}
					else
					{
						MeshComponents[0]->AddInstanceWorldSpace(Trans);
					}
				}
				Shifted = !Shifted;
			}
		}
		
		break;

	case ERenderMode::EHeightMap:
		UE_LOG(Editor, Warning, TEXT("No support for height information yet"));
		return false;
		{int32 X = 0; }
	default:
		// We shouldn't end up here, but if we do just return
		UE_LOG(Editor, Warning, TEXT("Redraw map has no fitting behaviour"));
		return false;
	}
	// If we reach the end of the switch, everything should be alright
	return true;
}

FVector2D UEditorRenderComponent::GetTileMeshDim()
{
	return TileMeshDim;
}


void UEditorRenderComponent::ClearMap()
{
	// Make sure to destroy every instances of each mesh component and empty the array afterwards
	for (int32 MeshComp = 0; MeshComp < MeshComponents.Num(); MeshComp++)
	{
		MeshComponents[MeshComp]->ClearInstances();
	}
	MeshComponents.Empty();

	// Delete the id informations as well
	InstanceIDs.Empty();
}

// Called every frame
//void UEditorRenderComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
//{
//	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
//
//}