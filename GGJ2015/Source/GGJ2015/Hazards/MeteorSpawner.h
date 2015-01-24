// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Meteor.h"
#include "MeteorSpawner.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2015_API AMeteorSpawner : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	void SpawnMeteor();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GGJ2015)
	float Delay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GGJ2015)
	float Interval;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GGJ2015)
	float Scale;

	float TimeAlive;

	UPROPERTY(EditDefaultsOnly, Category = GGJ2015)
	TSubclassOf<AMeteor> MeteorClass;
	UPROPERTY(EditDefaultsOnly, Category = GGJ2015)
	TSubclassOf<AActor> IndicatorClass;
};
