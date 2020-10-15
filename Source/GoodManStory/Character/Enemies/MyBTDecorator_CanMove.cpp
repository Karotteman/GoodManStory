// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_CanMove.h"

#include "AIController.h"
#include "BaseEnemy.h"
bool UMyBTDecorator_CanMove::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    ABaseEnemy* enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
    
    if(enemy->bAttacking)
        return false;
    else
        return true;
}
