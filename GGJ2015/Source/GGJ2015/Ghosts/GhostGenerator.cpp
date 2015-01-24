// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "GameMode/GGJ2015Character.h"
#include "GameMode/GGJ2015GameInstance.h"
#include "GhostGenerator.h"
#include "GhostLoader.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "GhostIO.h"

AGhostGenerator::AGhostGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TrackingInterval = 0.5f;
	Died = false;
}


void AGhostGenerator::BeginPlay()
{
	Super::BeginPlay();

	// Find the first player, track him
	for (TActorIterator<AGGJ2015Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TrackedActor = *ActorItr;
		TrackedActor->Generator = this;
		break;
	}

	// If no character found, do nothing
	if (!TrackedActor)
		return;

	// Start tracking
	TrackingTime = 0;
	GetWorldTimerManager().SetTimer(this, &AGhostGenerator::UpdateTracking, TrackingInterval, true);
}

void AGhostGenerator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("Bye"));

	if (EndPlayReason != EEndPlayReason::LevelTransition)
		return;

	UGGJ2015GameInstance * GI = Cast<UGGJ2015GameInstance>(GetGameInstance());
	if (!GI)
		return;

	GhostData.Name = GI->PlayerName;
	GhostData.TimeRemaining = TrackingTime;
	GhostIO::WriteGhostData(GetWorld()->GetMapName(), GhostData);
}

void AGhostGenerator::UpdateTracking()
{
	TrackingTime += TrackingInterval;

	FGhostData_Keyframe Keyframe;
	Keyframe.Location = TrackedActor->GetActorLocation();
	Keyframe.TimeStamp = TrackingTime;

	GhostData.Keyframes.Add(Keyframe);
	UE_LOG(LogTemp, Warning, TEXT("Added keyframe: %s"), *Keyframe.Location.ToString());
}

void AGhostGenerator::CreateTestGhost()
{
	// Find the first ghost loader, call it
	for (TActorIterator<AGhostLoader> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AGhostLoader * Loader = *ActorItr;
		Loader->CreateGhost(GhostData);
		break;
	}
}

void AGhostGenerator::StoreEvent(EGhostEvent inEvent)
{
	FGhostData_Event Event;
	Event.Event = int32(inEvent);
	Event.TimeStamp = TrackingTime;

	GhostData.Events.Add(Event);
}

void AGhostGenerator::OnDeath()
{
	if (Died)
		return;
	Died = true;

	TArray<FGhostData> GhostDatas = GhostIO::LoadGhostData(GetWorld()->GetMapName());
	int32 NumBefore = 0;
	int32 NumAfter = 0;
	for (auto Itr = GhostDatas.CreateConstIterator(); Itr; ++Itr)
	{
		const FGhostData& GhostData = *Itr;
		if (GhostData.TimeRemaining > TrackingTime)
			NumAfter++;
		else
			NumBefore++;
	}

	TrackedActor->GetCharacterMovement()->Velocity = FVector(0, 0, 0);

	const int32 TimeSeconds = FMath::RoundToInt(TrackingTime);
	BP_ShowScore(TimeSeconds, NumBefore, NumAfter);
}