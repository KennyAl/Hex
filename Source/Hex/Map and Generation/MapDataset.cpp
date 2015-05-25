// Fill out your copyright notice in the Description page of Project Settings.

#include "Hex.h"
#include "MapDataset.h"

UMapDataset::UMapDataset()
{
}

UMapDataset::UMapDataset(IVector2 Size)
{
	Resize(Size);
}
void UMapDataset::Resize(IVector2 NewSize)
{
	Tiles.Empty();
	TArray<FsTile*> InitHelper;
	InitHelper.Init(new FsTile, NewSize.Y);
	Tiles.Init(InitHelper, NewSize.X);
}

FsTile UMapDataset::GetTile(int32 X, int32 Y)
{
	return *Tiles[X][Y];
}

