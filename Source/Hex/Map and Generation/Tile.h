// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IVector.h"
#include "Tile.generated.h"

/** The different biomes a tile might have */
UENUM(BlueprintType)
enum class EBiomes : uint8
{
	EDefault	UMETA(DisplayName = "Default"),
};


/**
* Storing all informations about a single tile
*/
USTRUCT(BlueprintType)
struct FsTile
{
	GENERATED_USTRUCT_BODY()
	
	/** The biome that this tile has */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Utilities | Map Data")
	EBiomes Biome;

	/**
	* The altitude this tile has
	* 7 (max height)
	* .
	* .
	* 0 (sea level)
	* .
	* .
	* -4 (deep ocean)
	*/
	int32 Altitude;

	/** 
	* Position of the tile within the grid 
	* Seems kind of redundant, but it could be useful when you receive a pointer to a tile and want to
	* find out it's position
	*/
	// TODO: Maybe add support for blueprints in the future, if necessary
	IVector3 Coords;

	/**
	* Position of the tile in worldspace
	* MAYBE THIS WILL BE REPLAYED BY A METHOD TO CALCULATE THE TILES POSITION IF NECCESSARRY
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Utilities | Map Data")
	FVector WorldPosition;
	
	/** True if this tile is land, use for quick checks (faster than performing checks with the biome) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Utilities | Map Data")
	bool IsLand;

};