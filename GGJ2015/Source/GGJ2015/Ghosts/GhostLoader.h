// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GhostCharacter.h"
#include "GhostData.h"
#include "GhostLoader.generated.h"

/**
 * Loads ghost actors on start up
 */
UCLASS()
class GGJ2015_API AGhostLoader : public AActor
{
	GENERATED_UCLASS_BODY()
		
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
	
public:
	void CreateGhost(FGhostData GhostData);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGhostCharacter> CharacterClass;
	UPROPERTY(EditDefaultsOnly)
	bool EnableGhosts;
	
};
