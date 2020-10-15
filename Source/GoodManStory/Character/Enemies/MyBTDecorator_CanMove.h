// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_CanMove.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API UMyBTDecorator_CanMove : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
