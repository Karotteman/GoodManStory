// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_SetAvoidance.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API UMyBTService_SetAvoidance : public UBTService_BlackboardBase
{
    GENERATED_BODY()
public:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
