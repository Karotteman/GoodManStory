// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "GameFramework/Character.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DesktopPlatform/Private/Windows/WindowsNativeFeedbackContext.h"
#include "BaseEnemy_AIController.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GoodManStory/Character/Players/BasePlayer.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1
#define COLLISION_CHANNEL_ENEMY ECC_GameTraceChannel3

ABaseEnemy::ABaseEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap); 
    GetCapsuleComponent()->SetCollisionObjectType(COLLISION_CHANNEL_ENEMY);
    GetCapsuleComponent()->ComponentTags.Add(FName("Body"));

    AutoPossessAI = EAutoPossessAI::Spawned;
}

void ABaseEnemy::Kill()
{
    Super::Kill();
    
    GetMesh()->SetCollisionProfileName("Ragdoll");
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);

    BoxWeapon->DestroyComponent();
    BoxShield->DestroyComponent();
    
    GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
    Cast<AAIController>(GetController())->BrainComponent->StopLogic(TEXT("dead"));
    GetCharacterMovement()->SetAvoidanceEnabled(false);

    ABasePlayer* player = Cast<ABasePlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(!player->EvilSpellIsActive())
        player->EvilHealing();
}

void ABaseEnemy::SetIsStun(bool bNewStun) noexcept
{
    Super::SetIsStun(bNewStun);
    Cast<ABaseEnemy_AIController>(GetController())->SetPaused(bNewStun);
    
    if (bNewStun)
    {
        StopAnimMontage();
        bAttacking = false;
        AttackActiveHitBox(false, BoxWeapon);
        AttackActiveHitBox(false, BoxShield);
    }
}