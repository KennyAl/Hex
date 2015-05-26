// Fill out your copyright notice in the Description page of Project Settings.

#include "Hex.h"
#include "EditorMap.h"


AEditorMap::AEditorMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene Component"));
	RootComponent = SceneComp;
	MapData = ObjectInitializer.CreateDefaultSubobject<UMapDataset>(this, TEXT("MapData"));

}

void AEditorMap::BeginPlay()
{
	Super::BeginPlay();
	
}

UMapDataset* AEditorMap::GetMapData()
{
	return MapData;
}

