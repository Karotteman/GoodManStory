// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"

#include <Utility/Utility.h>


#include "BaseBoss.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "MemPro/MemPro.h"


void ABossAIController::BeginPlay()
{
    Super::BeginPlay();    

    if(BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("BehaviorTree null"));

    Blackboard->SetValueAsObject("Player", GetWorld()->GetFirstPlayerController()->GetPawn());
    
    BrainComponent->PauseLogic("Pause");
    StopMovement();
}


void ABossAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    ABaseBoss* pBoss = Cast<ABaseBoss>(InPawn);
    
    if(pBoss && Blackboard)
    {
        Blackboard->SetValueAsFloat("AttackRadius", pBoss->GetRangeAttack());
        Blackboard->SetValueAsFloat("PunchCooldown", pBoss->GetPunchCooldown());
        Blackboard->SetValueAsFloat("GroundAttackCooldown", pBoss->GetGroundAttackCooldown());
        Blackboard->SetValueAsFloat("FireBoalAttackCoolDown", pBoss->GetFireBallAttackCoolDown());
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Boss or blackboard null"));
}

void ABossAIController::StartBehaviours()
{
    BrainComponent->ResumeLogic("StopPause");
}
