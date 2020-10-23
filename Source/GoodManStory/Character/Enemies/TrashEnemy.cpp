// Fill out your copyright notice in the Description page of Project Settings.


#include "TrashEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "GoodManStory/Character/Players/BasePlayer.h"

#define COLLISION_CHANNEL_TRASH ECC_GameTraceChannel2

ATrashEnemy::ATrashEnemy()
{
    RightHandObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
    RightHandObject->SetupAttachment(GetMesh(), "hand_r");
    RightHandObject->SetRelativeScale3D({1.f, 1.f, 1.f});
    RightHandObject->SetRelativeRotation({0.f, 0.f, -90.f});
    RightHandObject->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RightHandObject->SetRelativeLocation({-15.f, 5.f, 0.f});
    RightHandObject->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    
    BoxWeapon = CreateDefaultSubobject<UBoxComponent>("BoxWeapon");
    BoxWeapon->SetupAttachment(RightHandObject);
    BoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BoxWeapon->OnComponentBeginOverlap.AddDynamic(this, &ATrashEnemy::OnRightHandObjectBeginOverlap);
    BoxWeapon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    BoxWeapon->SetCollisionObjectType(COLLISION_CHANNEL_TRASH);
    BoxWeapon->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);
    BoxWeapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

    GetCapsuleComponent()->SetCollisionObjectType(COLLISION_CHANNEL_TRASH);
    
    LeftHandObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
    LeftHandObject->SetupAttachment(GetMesh(), "hand_l");
    LeftHandObject->SetRelativeScale3D({1.f, 1.f, 1.f});
    LeftHandObject->SetRelativeRotation({0.f, 0.f, 0.f});
    LeftHandObject->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LeftHandObject->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    
    BoxShield = CreateDefaultSubobject<UBoxComponent>("BoxShield");
    BoxShield->SetupAttachment(LeftHandObject);
    BoxShield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BoxShield->OnComponentBeginOverlap.AddDynamic(this, &ATrashEnemy::OnLeftHandObjectBeginOverlap);
    BoxShield->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    BoxShield->SetCollisionObjectType(COLLISION_CHANNEL_TRASH);
    BoxShield->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);
    BoxShield->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void ATrashEnemy::OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{   
    if(OtherComp->ComponentHasTag("PlayerBody"))
    {
         ABasePlayer* player = Cast<ABasePlayer>(OtherActor);
         player->TakeDamageCharacter(Damage);
    }
}

void ATrashEnemy::Kill()
{
    Super::Kill();

}
