// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "GGJ2015.h"
#include "GGJ2015GameMode.h"
#include "GGJ2015PlayerController.h"
#include "GGJ2015Character.h"

AGGJ2015GameMode::AGGJ2015GameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = AGGJ2015PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}