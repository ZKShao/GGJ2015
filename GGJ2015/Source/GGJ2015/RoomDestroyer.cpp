// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "RoomDestroyer.h"
#include "EngineUtils.h"

void ARoomDestroyer::DestroyRoomWithTag(FName targetTag) {
  
  //Loop over all static mesh actors
  TActorIterator<AStaticMeshActor> allActorsIt = TActorIterator<AStaticMeshActor>(GetWorld());
     
  //While not reached end (overloaded bool operator)
  while (allActorsIt)
  {

    //If it has the tag, call the DestroyObject function on it
    if (allActorsIt->ActorHasTag(targetTag)) {
      DestroyObject(*allActorsIt);
    }
         
    //Advance iterator
    ++allActorsIt;
  }

}

//DestroyObject(AStaticMeshActor target)


