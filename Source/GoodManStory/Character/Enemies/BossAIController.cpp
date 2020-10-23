// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"


#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


void ABossAIController::BeginPlay()
{
    Super::BeginPlay();
    RunBehaviorTree(BehaviorTree);
    Blackboard->SetValueAsObject("Player", GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ABossAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    ABaseEnemy* enemy = Cast<ABaseEnemy>(InPawn);

    if (enemy != nullptr) { }
    else
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Enemy Null"));
}
