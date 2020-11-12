// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy_AIController.h"

#include <Utility/Utility.h>


#include "BaseEnemy.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

void ABaseEnemy_AIController::BeginPlay()
{
    Super::BeginPlay();
    
    if(BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("BehaviorTree null"));
    
    Blackboard->SetValueAsObject("Player", GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ABaseEnemy_AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    ABaseEnemy* enemy = Cast<ABaseEnemy>(InPawn);
    
    if(enemy != nullptr)
    {
        Blackboard->SetValueAsFloat("Radius", enemy->GetRangeAttack());
        Blackboard->SetValueAsFloat("TimeNextAttack", enemy->GetTimeToNextAttack());
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Enemy Null"));
}

void ABaseEnemy_AIController::SetPaused(bool bNewFlag)
{
    if (bNewFlag)
    {
        BrainComponent->PauseLogic("Stun");
        StopMovement();
    }
    else
    {
        BrainComponent->ResumeLogic("StopStun");
    }
}