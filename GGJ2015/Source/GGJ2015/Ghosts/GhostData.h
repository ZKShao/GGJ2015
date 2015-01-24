// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GhostEvent.h"
#include "GhostData.generated.h"

/**
 * Ghost movement keyframe
 */
USTRUCT()
struct GGJ2015_API FGhostData_Keyframe
{
	GENERATED_USTRUCT_BODY()

	FVector		Location;
	float		TimeStamp;
};
/**
 * Ghost event point
 */
USTRUCT()
struct GGJ2015_API FGhostData_Event
{
	GENERATED_USTRUCT_BODY()

	int32		Event;
	float		TimeStamp;
};

/**
 * All data for ghost playback
 */
USTRUCT()
struct GGJ2015_API FGhostData
{
	GENERATED_USTRUCT_BODY()

	FString Name;
	float TimeRemaining;

	TArray<FGhostData_Keyframe> Keyframes;
	TArray<FGhostData_Event> Events;
	
};
