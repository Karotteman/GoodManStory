// Fill out your copyright notice in the Description page of Project Settings.


#include "MonoHitBehaviours.h"

#include <Utility/Utility.h>

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UMonoHitBehaviours::UMonoHitBehaviours()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ActorAlreadyHit.Reserve(8);
}


// Called when the game starts
void UMonoHitBehaviours::BeginPlay()
{
	Super::BeginPlay();
}

void UMonoHitBehaviours::Reset()
{
	ActorAlreadyHit.Reset();
}

bool UMonoHitBehaviours::CheckIfAlreadyExistAndAdd(AActor* pNewActor)
{
	if(UNLIKELY(IsAlreadyExist(pNewActor)))
	{
		return true;
	}
	else
	{
		ActorAlreadyHit.Add(pNewActor);
		return false;
	}
}

bool UMonoHitBehaviours::IsAlreadyExist(AActor* pActor)
{
	return ActorAlreadyHit.Find(pActor) != INDEX_NONE;
}

