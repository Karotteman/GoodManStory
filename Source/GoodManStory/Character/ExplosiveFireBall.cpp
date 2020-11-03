// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveFireBall.h"

#include "Players/BasePlayer.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1
#define COLLISION_CHANNEL_TRASH ECC_GameTraceChannel2
#define COLLISION_CHANNEL_ENEMY ECC_GameTraceChannel3
#define COLLISION_CHANNEL_FIREBALL ECC_GameTraceChannel4

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
        const float ChocForceWithDistance = ChocForce * (ChocForceDependingOfDistance ? 1.f : 1.f - (LaunchForce
        .SizeSquared() / (ChocWaveZone->GetScaledSphereRadius() * ChocWaveZone->GetScaledSphereRadius())));
        LaunchForce.Normalize();
        LaunchForce *= ChocForceWithDistance;
        LaunchForce.Z = ChocForceHeightRatio * ChocForceWithDistance;

        ABasePlayer* pPlayer = Cast<ABasePlayer>(pActor);

        if (pPlayer)
        {
            pPlayer->TakeDamageCharacter(Damage);
        }

        pCharacter->LaunchAndStun(LaunchForce, true, true);
    }

    OnChocWave.Broadcast();

    if (!DestroyOnlyIfGroundTagFound || OtherComp->ComponentHasTag(TEXT("FireBallDestroyable")))
    {
        Destroy();
    }
}

AExplosiveFireBall::AExplosiveFireBall()
{
    ChocWaveZone = CreateDefaultSubobject<USphereComponent>("ChocWaveZone");
    ChocWaveZone->SetupAttachment(Collider);
    ChocWaveZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
    ChocWaveZone->SetCollisionObjectType(COLLISION_CHANNEL_FIREBALL);
    ChocWaveZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    ChocWaveZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    ChocWaveZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Overlap);
}
