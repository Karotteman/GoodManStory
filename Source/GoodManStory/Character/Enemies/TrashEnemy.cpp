// Fill out your copyright notice in the Description page of Project Settings.


#include "TrashEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

#define COLLISION_CHANNEL_TRASH ECC_GameTraceChannel2


ATrashEnemy::ATrashEnemy()
{
    Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(GetMesh(), "hand_r");
    Weapon->SetRelativeScale3D({1.f, 1.f, 1.f});
    Weapon->SetRelativeRotation({0.f, 0.f, -90.f});
    Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Weapon->SetRelativeLocation({-15.f, 5.f, 0.f});

    Weapon->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);
    Weapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    
    BoxWeapon = CreateDefaultSubobject<UBoxComponent>("BoxWeapon");
    BoxWeapon->SetupAttachment(Weapon);
    BoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BoxWeapon->OnComponentBeginOverlap.AddDynamic(this, &ATrashEnemy::OnWeaponBeginOverlap);
    BoxWeapon->SetCollisionObjectType(COLLISION_CHANNEL_TRASH);
    BoxWeapon->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);
    BoxWeapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

    Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
    Shield->SetupAttachment(GetMesh(), "hand_l");
    Shield->SetRelativeScale3D({1.f, 1.f, 1.f});
    Shield->SetRelativeRotation({0.f, 0.f, 0.f});
    Shield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Shield->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);
    Shield->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    
    BoxShield = CreateDefaultSubobject<UBoxComponent>("BoxShield");
    BoxShield->SetupAttachment(Shield);
    BoxShield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BoxShield->OnComponentBeginOverlap.AddDynamic(this, &ATrashEnemy::OnWeaponBeginOverlap);
    BoxShield->SetCollisionObjectType(COLLISION_CHANNEL_TRASH);
    BoxShield->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);
    BoxShield->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}


void ATrashEnemy::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherComp->ComponentHasTag("Player"))
    {
                
    }
}

void ATrashEnemy::Kill()
{
    Super::Kill();

}
