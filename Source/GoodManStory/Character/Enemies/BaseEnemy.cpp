// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DesktopPlatform/Private/Windows/WindowsNativeFeedbackContext.h"
#include "Engine/Channel.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Physics/PhysicsFiltering.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1
#define COLLISION_CHANNEL_ENEMY ECC_GameTraceChannel3

ABaseEnemy::ABaseEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap); 
    GetCapsuleComponent()->SetCollisionObjectType(COLLISION_CHANNEL_ENEMY);
    GetCapsuleComponent()->ComponentTags.Add(FName("Body"));
}

void ABaseEnemy::Kill()
{
    Super::Kill();
    
    GetMesh()->SetCollisionProfileName("Ragdoll");
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
    
    GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
    Cast<AAIController>(GetController())->BrainComponent->StopLogic(TEXT("dead"));
    GetCharacterMovement()->SetAvoidanceEnabled(false);
}
