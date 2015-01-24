// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "AIController.h"
#include "GhostCharacter.h"

AGhostCharacter::AGhostCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGhostCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TrackingTime += DeltaSeconds;
	UpdateMovement(DeltaSeconds);
	UpdateEvents(DeltaSeconds);
}

void AGhostCharacter::UpdateMovement(float DeltaSeconds)
{
	// If no frames left, do nothing
	if (GhostData.Keyframes.Num() <= 0)
	{
		Destroy();
		return;
	}

	// Check if next keyframe reached
	FGhostData_Keyframe& NextFrame = GhostData.Keyframes[0];
	if (TrackingTime > NextFrame.TimeStamp)
	{
		FVector CurrentLoc = NextFrame.Location;

		// Apply this keyframe and remove it
		SetActorLocation(CurrentLoc);
		GhostData.Keyframes.RemoveAt(0);

		if (GhostData.Keyframes.Num() > 0)
		{
			FVector NextLoc = GhostData.Keyframes[0].Location;
			FVector Diff = NextLoc - CurrentLoc;
			float OutLength = 0;
			Diff.ToDirectionAndLength(Direction, OutLength);
			OnDirectionChange(Direction);
		}
	}
	else
	{
		// Next keyframe is inbound, interpolate towards it
		FVector NextLocation = NextFrame.Location;
		FVector InterpLoc = FMath::VInterpConstantTo(GetActorLocation(), NextLocation, DeltaSeconds, 800);
		SetActorLocation(InterpLoc);
	}
}

void AGhostCharacter::UpdateEvents(float DeltaSeconds)
{
	if (GhostData.Events.Num() <= 0)
		return;
	
	FGhostData_Event& NextEvent = GhostData.Events[0];
	if (TrackingTime > NextEvent.TimeStamp)
	{
		// Fire event and remove it
		OnGhostEvent(EGhostEvent(NextEvent.Event));
		GhostData.Events.RemoveAt(0);
	}
}

void AGhostCharacter::InitGhost(FGhostData inGhostData)
{
	TrackingTime = 0;
	GhostData = inGhostData;

	OnGhostInit(GhostData.Name, GhostData.TimeRemaining);
}