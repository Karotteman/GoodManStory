// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonoHitBehaviours.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOODMANSTORY_API UMonoHitBehaviours : public UActorComponent
{
	GENERATED_BODY()

protected:
	TArray<class AActor*> ActorAlreadyHit;
	
public:	
	// Sets default values for this component's properties
	UMonoHitBehaviours();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	UFUNCTION()
	void Reset();

	UFUNCTION()
	bool CheckIfAlreadyExistAndAdd(class AActor* pNewActor);
	
	UFUNCTION()
	bool IsAlreadyExist(class AActor* pActor);
};
