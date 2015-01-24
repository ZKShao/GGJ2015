// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MeteorSpawner.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2015_API AMeteorSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	void SpawnMeteor();
	
	UPROPERTY(EditAnywhere, Category = GGJ2015)
	float Delay;

	UPROPERTY(EditDefaultsOnly, Category = GGJ2015)
	TSubclassOf<AActor> MeteorClass;

};
