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

void AGGJ2015Character::StoreEvent(EGhostEvent Event)
{
	if (!Generator)
		return;
	Generator->StoreEvent(Event);
}

FString AGGJ2015Character::GetVelocityFacing(FVector velocity) {

  //Idle
  if (velocity.Size() == 0.f)
    return "Idle";

  TArray<float> dotProducts;
  dotProducts.Init(4);
  //Right
  dotProducts[0] = FVector::DotProduct(velocity, FVector(1.f, 0.f, 0.f));
  //Left
  dotProducts[1] = FVector::DotProduct(velocity, FVector(-1.f, 0.f, 0.f));
  //Up
  dotProducts[2] = FVector::DotProduct(velocity, FVector(0.f, -1.f, 0.f));
  //Down
  dotProducts[3] = FVector::DotProduct(velocity, FVector(0.f, 1.f, 0.f));

  int maxIndex;
  FMath::Max<float>(dotProducts, &maxIndex);

  switch (maxIndex) {
  case 0: return "R";
  case 1: return "L";
  case 2: return "U";
  case 3: return "D";
  }

  return "Idle";
}
