// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MapDataset.h"
#include "Components/ActorComponent.h"
#include "EditorRenderComponent.generated.h"


/** The different modes that are available */
UENUM(BlueprintType)
enum class ERenderMode :uint8
{
	/** Not drawing anything for now, choosing this option will free all allocated resources */
	ENone			UMETA(DisplayName = "None"),

	/** Displaying water on one level and everything else on another */
	ELandMass		UMETA(DisplayName = "LandMass"),

	/** Drawing height information with colors and meshes defined in the settings */
	EHeightMap		UMETA(DisplayName = "HeightMap"),
};

/** A pair of an index within the array of dynamically created instanced mesh components 
* and the id of the instance that represents a tile in the editor
*/
struct sInstanceIDs
{
	int32 ID = 0;

	int32 MeshIndex = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEX_API UEditorRenderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values for this component's properties */
	UEditorRenderComponent(const FObjectInitializer& ObjectInitializer);

	/** Called when the game starts */
	virtual void InitializeComponent() override;
	
	// Called every frame
	//virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Holding the static mesh, the instanced mesh comp should have */
	TArray<UInstancedStaticMeshComponent*> Inst;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TEST)
	UStaticMesh* Mesh;

	/** For testing the dynamically adding of uobjects */
	UFUNCTION(BlueprintCallable, Category = TEST)
	void TEST_DynamicComps();

	/** Performs checks and sets the dataset being used 
	* @param MapData	Pointer to the map data
	*/
	void Init(UMapDataset* NewMapData);

	/** Change the render mode and redraw the map
	* @param NewRenderMode	The desired render mode
	*/
	UFUNCTION(BlueprintCallable, Category="Map Utilities | Editor Visuals")
	void SwitchRenderMode(ERenderMode NewRenderMode);
	
	/** Redraws the entire map, taking the render mode into consideration
	* @returns True if successful
	*/
	UFUNCTION(BlueprintCallable, Category = "Map Utilities | Editor Visuals")
	bool RedrawMap();

	/** Returns the dimensions of the mesh that is currently in use */
	UFUNCTION(BlueprintPure, Category="Map Utilities | Editor Visuals")
	FVector2D GetTileMeshDim();
	

	//
	// Editor Settings
	//
	
	/** The meshes that will be used to represent the different altitudes
	* [0]	 -> deepest ocean
	* [max]	 -> heighest mountain
	* When changing the amount of meshes or materials "water level index" must be updated as well
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map Utilities | Editor Visuals")
	TArray<UStaticMesh*> AltitudeMeshes;
	
	/** The materials that will be used to represent the different altitudes
	* [0]	 -> deepest ocean
	* [max]	 -> heighest mountain
	* When changing the amount of meshes or materials "water level index" must be updated as well
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map Utilities | Editor Visuals")
	TArray<UMaterial*> AltitudeMaterials;

	/** The index of the mesh or material that should be used as the water level */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map Utilities | Editor Visuals")
	int32 WaterLevelIndex;

	/** If set to true, all meshes will cast shadows, default is true */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map Utilities | Editor Visuals")
	bool bCastShadows;

	/** The scale of the tile meshes:
	* Scale.X -> X/Y
	* Scale.Y -> Z
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map Utilities | Editor Visuals")
	FVector2D Scale;
private:

	/** Deletes everything in InstanceIDs and MeshComponents */
	void ClearMap();

	/** True if the renderer is initialized */
	bool bIsInitialized;
	
	/** Pointer to the map data currently used */
	UMapDataset* MapData;

	/** The render mode that is currently set */
	ERenderMode RenderMode;

	/** The currently used instanced mesh components */
	TArray<UInstancedStaticMeshComponent*> MeshComponents;

	/** For each tile on the map, this stores which instanced mesh component is being used
	* and which id the instance of this component has, so we know which instance to delete
	* if we want to redraw a tile
	*/
	TArray<TArray<sInstanceIDs>> InstanceIDs;

	/** Stores the height and width of the used tile meshes 
	* Since X and Y are reversed in the tile map, this is reversed too
	* (X in worldspace -> Y in the tile map)
	*/
	FVector2D TileMeshDim;
};
