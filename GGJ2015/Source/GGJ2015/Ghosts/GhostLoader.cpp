// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "GhostLoader.h"
#include "GhostIO.h"

AGhostLoader::AGhostLoader(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	EnableGhosts = true;
}

void AGhostLoader::BeginPlay() 
{
	if (!EnableGhosts)
		return;

	TArray<FGhostData> GhostDatas = GhostIO::LoadGhostData(GetWorld()->GetMapName());
	for (auto Itr = GhostDatas.CreateIterator(); Itr; ++Itr)
		CreateGhost(*Itr);
}

void AGhostLoader::CreateGhost(FGhostData GhostData)
{
	if (!CharacterClass || GhostData.Keyframes.Num() <= 0)
		return;

	FVector SpawnLoc = GhostData.Keyframes[0].Location;
	AGhostCharacter * Char = Cast<AGhostCharacter>(GetWorld()->SpawnActor(CharacterClass, &SpawnLoc));
	if (!Char)
		return;

	Char->InitGhost(GhostData);
	Char->SpawnDefaultController();
}