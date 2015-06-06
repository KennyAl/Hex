// Fill out your copyright notice in the Description page of Project Settings.

#include "Hex.h"
#include "MapDataset.h"

UMapDataset::UMapDataset()
{
}

UMapDataset::UMapDataset(IVector2 NewSize)
{
	Resize(NewSize);
}

void UMapDataset::Resize(IVector2 NewSize)
{
	Tiles.Empty();
	TArray<FsTile*> InitHelper;
	InitHelper.Init(nullptr, NewSize.Y);
	Tiles.Init(InitHelper, NewSize.X);
	for (int32 X = 0; X < NewSize.X; X++)
	{
		for (int32 Y = 0; Y < NewSize.Y; Y++)
		{
			Tiles[X][Y] = new FsTile;
		}
	}
	Size = NewSize;
}

FsTile UMapDataset::GetTile(int32 X, int32 Y)
{
	return *Tiles[X][Y];
}

