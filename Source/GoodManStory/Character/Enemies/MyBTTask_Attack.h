// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API UMyBTTask_Attack : public UBTTask_BlackboardBase
{
    GENERATED_BODY()
public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
