// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Meteor.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2015_API AMeteor : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GGJ2015)
	FVector Velocity;
	
};
