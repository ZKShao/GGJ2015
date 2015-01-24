// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "MeteorSpawner.h"
#include "GameMode/GGJ2015Character.h"
#include "Engine.h"
#include "EngineUtils.h"

AMeteorSpawner::AMeteorSpawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TimeAlive = 0;
	Delay = 3;
	Interval = 1;
	Scale = 1;
}

void AMeteorSpawner::BeginPlay()
{
	GetWorldTimerManager().SetTimer(this, &AMeteorSpawner::SpawnMeteor, Interval, true, Delay);
	TimeAlive += Delay;
}

void AMeteorSpawner::SpawnMeteor()
{
	if (!MeteorClass || !IndicatorClass)
		return;

	FVector MyLoc = GetActorLocation();
	for (TActorIterator<AGGJ2015Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		FVector PlayerLoc = ActorItr->GetActorLocation();
		if (FVector::Dist(PlayerLoc, MyLoc) > 10000)
			return;
	}

	const float SpeedBoost = FMath::Max<float>(TimeAlive - 30, 0) / 30;
	const float SpeedScale = 1 + FMath::Sqrt(SpeedBoost);
	FActorSpawnParameters Params;
	Params.bNoCollisionFail = true;
	Params.bNoFail = true;

	FVector SpawnLoc = GetActorLocation() + FVector(0, 0, 1000);
	FRotator SpawnRot = FRotator(0, 0, 0);
	AMeteor * Meteor = Cast<AMeteor>(GetWorld()->SpawnActor(MeteorClass, &SpawnLoc, &SpawnRot, Params));
	Meteor->SetActorScale3D(FVector(Scale, Scale, Scale));
	Meteor->Velocity = SpeedScale * Meteor->Velocity;
	TimeAlive += Interval;

	AActor * Indicator = GetWorld()->SpawnActor(IndicatorClass, &MyLoc, &SpawnRot, Params);
	Indicator->SetActorScale3D(FVector(Scale, Scale, Scale));
}

