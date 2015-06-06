// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "Object.h"
#include "MapDataset.generated.h"

/**
 * Base class for a set of tile data with 
 */
UCLASS(Blueprintable)
class HEX_API UMapDataset : public UObject
{
	GENERATED_BODY()
public:

	/** Default constructor, empty dataset */
	UMapDataset();

	/** This constructor resizes the dataset at initialization
	* @param NewSize	The size that the dataset should have
	*/
	UMapDataset(IVector2 NewSize);

	/** Resizes the dataset, and fills it with default tiles
	* @param NewSize	The new size the dataset should have
	*/
	void Resize(IVector2 NewSize);

	/** Returns a pointer to the tile at a given pair of coordinates
	* @param Coords	The coordinates
	* @returns		Pointer to the tile
	*/
	FORCEINLINE FsTile* GetTile(IVector2 Coords){ return Tiles[Coords.X][Coords.Y]; }

	/** Returns the tile at a given pair of coordinates, blueprint version
	* @param X		The x coordinate
	* @param Y		The Y coordinate
	* @returns		The tile
	*/
	UFUNCTION(BlueprintPure, Category = "Map Utilities | Map Data")
	FsTile GetTile(int32 X, int32 Y);

	/** Returns the size of the map */
	FORCEINLINE const IVector2* GetSize(){ return &Size; }
	


private:

	/** The tile data */
	TArray<TArray<FsTile*>> Tiles;

	/** The size of the map */
	IVector2 Size;
};
