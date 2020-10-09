// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_SetAvoidance.h"

#include "AIController.h"
#include "BaseEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GoodManStory/Character/Players/BasePlayer.h"


void UMyBTService_SetAvoidance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ABaseEnemy* enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
    AActor*     player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
    float       DistEnemyPlayer = (enemy->GetActorLocation() - player->GetActorLocation()).Size();

    float NewAvoidance = enemy->GetMinAvoidanceRadius() + DistEnemyPlayer * enemy->GetMaxAvoidanceRadius() / enemy->
        GetAvoidanceLimitDistance();

    if (NewAvoidance > enemy->GetMaxAvoidanceRadius())
        NewAvoidance = enemy->GetMaxAvoidanceRadius();
    //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf("%f", NewAvoidance));

    enemy->GetCharacterMovement()->AvoidanceConsiderationRadius = NewAvoidance;
}
