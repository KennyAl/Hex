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
* Stores all informations about a single tile
*/
USTRUCT(BlueprintType)
struct FsTile
{
	GENERATED_USTRUCT_BODY()
	
	/** The biome this tile has */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Utilities | Map Data")
	EBiomes Biome = EBiomes::EDefault;

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
	int32 Altitude = 0;

	/** 
	* Position of the tile within the grid 
	* Seems kind of redundant, but it could be useful when you receive a pointer to a tile and want to
	* find out it's position
	*/
	// TODO: Maybe add support for blueprints in the future, if necessary
	IVector3 Coords(0);

	/**
	* Position of the tile in worldspace
	* MAYBE THIS WILL BE REPLACED BY A METHOD TO CALCULATE THE TILES POSITION IF NECCESSARRY
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Utilities | Map Data")
	FVector WorldPosition(0);
	
	/** True if this tile is land, use for quick checks (faster than performing checks with the biome) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Utilities | Map Data")
	bool IsLand = false;

};