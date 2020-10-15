// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_IsInRange.h"


#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GoodManStory/Character/BaseCharacter.h"
#include "../Players/BasePlayer.h"
#include "Engine/Engine.h"

bool UMyBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    float radius = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(Range.SelectedKeyName);

    ABasePlayer* player = Cast<ABasePlayer>(
        OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));

    if (player != nullptr)
    {
        float distPlayerEnemy = (player->GetActorLocation() - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()).
            Size();
        if (radius >= distPlayerEnemy)
            return true;
        else
            return false;
    }
    else
        return false;
}
