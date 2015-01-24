// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "GGJ2015GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2015_API UGGJ2015GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = GGJ2015)
	void SetPlayerName(FString inPlayerName);

	FString PlayerName;
	
	
};
