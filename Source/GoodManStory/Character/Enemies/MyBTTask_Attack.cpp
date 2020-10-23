// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Attack.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "Animation/AnimMontage.h"


EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ABaseEnemy* enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
    if(enemy != nullptr && !enemy->bAttacking)
    {
        enemy->bAttacking = true;
        enemy->PlayAnimMontage(enemy->Attack);
        return EBTNodeResult::Succeeded;
    }
    else
        return EBTNodeResult::Failed;
}
