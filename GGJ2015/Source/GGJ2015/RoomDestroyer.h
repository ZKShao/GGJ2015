// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "RoomDestroyer.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2015_API ARoomDestroyer : public AActor
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = GGJ2015)
  void DestroyRoomWithTag(FName targetTag);
	
  UFUNCTION(BlueprintImplementableEvent, Category = GGJ2015)
  void DestroyObject(AStaticMeshActor* target);
};
