// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "GGJ2015.h"
#include "GGJ2015Character.h"
#include "Ghosts/GhostGenerator.h"

AGGJ2015Character::AGGJ2015Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

float AGGJ2015Character::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	// Die
	if (Generator)
		Generator->OnDeath();
	return DamageAmount;
}

void AGGJ2015Character::StoreEvent(EGhostEvent Event)
{
	if (!Generator)
		return;
	Generator->StoreEvent(Event);
}
