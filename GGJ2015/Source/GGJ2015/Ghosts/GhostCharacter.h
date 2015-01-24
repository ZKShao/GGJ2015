// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GhostData.h"
#include "GhostEvent.h"
#include "GhostCharacter.generated.h"

/**
 * Plays back stored character data
 */
UCLASS()
class GGJ2015_API AGhostCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	// Begin AActor interface
	virtual void Tick(float DeltaSeconds) override;
	// End AActor interface

	void UpdateMovement(float DeltaSeconds);
	void UpdateEvents(float DeltaSeconds);

	UFUNCTION(BlueprintImplementableEvent, Category = GGJ2015)
	void OnGhostEvent(EGhostEvent Event);
	UFUNCTION(BlueprintImplementableEvent, Category = GGJ2015)
	void OnGhostInit(const FString& Name, float RemainingTime);
	UFUNCTION(BlueprintImplementableEvent, Category = GGJ2015)
	void OnDirectionChange(const FVector& Direction);
	
public:
	void InitGhost(FGhostData inGhostData);

	UPROPERTY(BlueprintReadOnly, Category = GGJ2015)
	FVector Direction;

	float				TrackingTime;
	FGhostData			GhostData;
	
};
