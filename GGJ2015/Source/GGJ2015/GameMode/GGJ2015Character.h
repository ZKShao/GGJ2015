// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

//#include "Runtime/Engine/Classes/PaperCharacter.h"
#include "PaperCharacter.h"
#include "GameFramework/Character.h"
#include "Ghosts/GhostEvent.h"
#include "GGJ2015Character.generated.h"

class AGhostGenerator;

UCLASS(Blueprintable)
class AGGJ2015Character : public APaperCharacter
{
	GENERATED_BODY()


public:
	AGGJ2015Character(const FObjectInitializer& ObjectInitializer);

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	UFUNCTION(BlueprintCallable, Category = GGJ2015)
	void StoreEvent(EGhostEvent Event);

	AGhostGenerator * Generator;

};

