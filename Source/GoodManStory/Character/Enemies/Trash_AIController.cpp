// Fill out your copyright notice in the Description page of Project Settings.


#include "Trash_AIController.h"

#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


void ATrash_AIController::BeginPlay()
{
    Super::BeginPlay();
    RunBehaviorTree(BehaviorTree);
    Blackboard->SetValueAsObject("Player", GetWorld()->GetFirstPlayerController()->GetPawn());


}


void ATrash_AIController::OnPossess(APawn* InPawn)
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
