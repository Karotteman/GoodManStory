// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveFireBall.h"

#include "Players/BasePlayer.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1
#define COLLISION_CHANNEL_TRASH ECC_GameTraceChannel2
#define COLLISION_CHANNEL_ENEMY ECC_GameTraceChannel3

void AExplosiveFireBall::OnFireBallBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    TArray<AActor*> pActorsOverllapingWithChocWave;

    ChocWaveZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ChocWaveZone->GetOverlappingActors(pActorsOverllapingWithChocWave, ABaseCharacter::StaticClass());
    ChocWaveZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    for (AActor* pActor : pActorsOverllapingWithChocWave)
    {
        ABaseCharacter* pCharacter = Cast<ABaseCharacter>(pActor);

        FVector LaunchForce = pActor->GetActorLocation() - GetActorLocation();
        LaunchForce.Normalize();
        LaunchForce *= ChocForce;
        LaunchForce.Z = ChocForceHeightRatio * ChocForce;

        ABasePlayer* pPlayer = Cast<ABasePlayer>(pActor);

        if (pPlayer)
        {
            pPlayer->TakeDamageCharacter(Damage);
        }

        pCharacter->LaunchCharacter(LaunchForce, true, true);
    }

    OnChocWave.Broadcast();
    Destroy();
}

AExplosiveFireBall::AExplosiveFireBall()
{
    ChocWaveZone = CreateDefaultSubobject<USphereComponent>("ChocWaveZone");
    ChocWaveZone->SetupAttachment(Collider);
    ChocWaveZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
    ChocWaveZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    ChocWaveZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    ChocWaveZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    ChocWaveZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Overlap);
}
