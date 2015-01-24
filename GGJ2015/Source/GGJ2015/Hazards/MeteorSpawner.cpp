// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "MeteorSpawner.h"
#include "Engine.h"
#include "EngineUtils.h"

void AMeteorSpawner::BeginPlay()
{
	GetWorldTimerManager().SetTimer(this, &AMeteorSpawner::SpawnMeteor, Delay, false);
}

void AMeteorSpawner::SpawnMeteor()
{
	if (!MeteorClass)
		return;

	FVector SpawnLoc = GetActorLocation() + FVector(0, 0, 1000);
	GetWorld()->SpawnActor(MeteorClass, &SpawnLoc);
}

