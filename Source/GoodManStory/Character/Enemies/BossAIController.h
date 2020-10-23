// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABossAIController : public AAIController
{
	GENERATED_BODY()

    protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BehaviorTree")
    UBehaviorTree* BehaviorTree;
    
    protected:
    virtual void BeginPlay() override;
    virtual  void OnPossess(APawn* InPawn) override;
};
