// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MapDataset.h"
#include "GameFramework/Actor.h"
#include "EditorMap.generated.h"

UCLASS()
class HEX_API AEditorMap : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	AEditorMap(const FObjectInitializer& ObjectInitializer);

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Returns a pointer to the mapdata */
	UFUNCTION(BlueprintPure, Category = "Map Utilities")
	UMapDataset* GetMapData();

protected:

	/** Used as the root component */
	USceneComponent* SceneComp;

private:

	/** MapData */
	UMapDataset* MapData;
};
