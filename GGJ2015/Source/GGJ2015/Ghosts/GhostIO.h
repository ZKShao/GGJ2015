// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GhostData.h"

class GhostIO
{
public:
	static void WriteGhostData(FString MapName, FGhostData Data);
	static TArray<FGhostData> LoadGhostData(FString MapName);
};