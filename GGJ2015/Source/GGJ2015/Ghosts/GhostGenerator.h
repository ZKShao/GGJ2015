// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GhostData.h"
#include "GhostGenerator.generated.h"

class AGGJ2015Character;

/**
 * Tracks a character and generates ghost data
 */
UCLASS()
class GGJ2015_API AGhostGenerator : public AActor
{
	GENERATED_UCLASS_BODY()

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	void UpdateTracking();

public:
	UFUNCTION(BlueprintCallable, Category = GGJ2015)
	void CreateTestGhost();

	UFUNCTION(BlueprintCallable, Category = GGJ2015)
	void StoreEvent(EGhostEvent Event);

	UPROPERTY(EditDefaultsOnly)
	float					TrackingInterval;

	float					TrackingTime;
	AGGJ2015Character *		TrackedActor;
	FGhostData				GhostData;
	
};
