// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Physics/PhysicsFiltering.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1

ABaseEnemy::ABaseEnemy()
{
    
}

void ABaseEnemy::Kill()
{
    Super::Kill();
    
    //GetMesh()->SetVisibility(false);
    GetMesh()->SetCollisionProfileName("Ragdoll");
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Ignore);
    
    GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
    
    Cast<AAIController>(GetController())->BrainComponent->StopLogic(TEXT("dead"));
}
