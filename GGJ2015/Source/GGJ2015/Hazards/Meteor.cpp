// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ2015.h"
#include "Meteor.h"

AMeteor::AMeteor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}