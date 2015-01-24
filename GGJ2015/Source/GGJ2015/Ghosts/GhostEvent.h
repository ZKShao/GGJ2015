// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GhostEvent.generated.h"

/**
 * All types of events simulated by ghosts.
 */
UENUM(BlueprintType)
enum class EGhostEvent : uint8
{
	Jump,
	Ping,

};