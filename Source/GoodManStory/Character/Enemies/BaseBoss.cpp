// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBoss.h"

#include <Utility/Utility.h>

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Controller.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "GoodManStory/Character/FireBall.h"
#include "GoodManStory/Character/Players/BasePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1
#define COLLISION_CHANNEL_TRASH ECC_GameTraceChannel2
#define COLLISION_CHANNEL_ENEMY ECC_GameTraceChannel3

void ABaseBoss::OnHandsObjectsBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                           const FHitResult&    SweepResult)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        ABasePlayer* player = Cast<ABasePlayer>(OtherActor);
        player->TakeDamageCharacter(PunchDamage);
    }
}

void ABaseBoss::OnBellyZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                        const FHitResult&    SweepResult)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnBellyZone = true;
    }
}

void ABaseBoss::OnBellyZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnBellyZone = false;
    }
}

void ABaseBoss::OnPunchZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                        const FHitResult&    SweepResult)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnPunchZone = true;
    }
}

void ABaseBoss::OnPunchZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnPunchZone = false;
    }
}

void ABaseBoss::OnGroundZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                         const FHitResult&    SweepResult)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnGroundZone = true;
    }
}

void ABaseBoss::OnGroundZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32        OtherBodyIndex)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnGroundZone = false;
    }
}

void ABaseBoss::OnGroundAttackZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult&    SweepResult)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnGroundAttackZone = true;
    }
}

void ABaseBoss::OnGroundAttackZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32        OtherBodyIndex)
{
    if (OtherComp->ComponentHasTag("PlayerBody"))
    {
        bPlayerIsOnGroundAttackZone = false;
    }
}

ABaseBoss::ABaseBoss()
{
    GetCapsuleComponent()->SetGenerateOverlapEvents(false);
    GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);

    GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetMesh()->SetGenerateOverlapEvents(false);
    GetMesh()->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    GetMesh()->SetCollisionObjectType(COLLISION_CHANNEL_ENEMY);
    GetMesh()->bMultiBodyOverlap = false;

    HeadCollision = CreateDefaultSubobject<USphereComponent>("Head");
    HeadCollision->SetupAttachment(GetMesh(), TEXT("headSocket"));
    HeadCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    HeadCollision->SetSphereRadius(32.f);
    HeadCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    HeadCollision->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    HeadCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
    HeadCollision->SetCollisionObjectType(COLLISION_CHANNEL_ENEMY);
    HeadCollision->ComponentTags.Add(TEXT("CharacterWeakZone"));
    HeadCollision->ComponentTags.Add(TEXT("Body"));
    
    PunchZone = CreateDefaultSubobject<USphereComponent>("PunchZone");
    PunchZone->SetupAttachment(GetCapsuleComponent());
    PunchZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    PunchZone->OnComponentBeginOverlap.AddDynamic(this, &ABaseBoss::OnPunchZoneBeginOverlap);
    PunchZone->OnComponentEndOverlap.AddDynamic(this, &ABaseBoss::OnPunchZoneEndOverlap);

    PunchZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    PunchZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    PunchZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    PunchZone->SetSphereRadius(PunchZoneRadius);

    BellyZone = CreateDefaultSubobject<UBoxComponent>("BellyZone");
    BellyZone->SetupAttachment(GetCapsuleComponent());
    BellyZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    BellyZone->OnComponentBeginOverlap.AddDynamic(this, &ABaseBoss::OnBellyZoneBeginOverlap);
    BellyZone->OnComponentEndOverlap.AddDynamic(this, &ABaseBoss::OnBellyZoneEndOverlap);

    BellyZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    BellyZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    BellyZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);

    BellyZone->SetBoxExtent(FVector{
        PunchZoneRadius,
        PunchZoneRadius,
        BellyZoneHeightRatio * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()
    });

    /*Ground attack setting*/
    GroundAttackZone = CreateDefaultSubobject<USphereComponent>("GroundAttackZone");
    GroundAttackZone->SetupAttachment(GetCapsuleComponent());
    GroundAttackZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    GroundAttackZone->OnComponentBeginOverlap.AddDynamic(this, &ABaseBoss::OnGroundAttackZoneBeginOverlap);
    GroundAttackZone->OnComponentEndOverlap.AddDynamic(this, &ABaseBoss::OnGroundAttackZoneEndOverlap);

    GroundAttackZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GroundAttackZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GroundAttackZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    GroundAttackZone->SetSphereRadius(GroundAttackZoneRadius);

    GroundZone = CreateDefaultSubobject<UBoxComponent>("GroundZone");
    GroundZone->SetupAttachment(GetCapsuleComponent());
    GroundZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    GroundZone->OnComponentBeginOverlap.AddDynamic(this, &ABaseBoss::OnGroundZoneBeginOverlap);
    GroundZone->OnComponentEndOverlap.AddDynamic(this, &ABaseBoss::OnGroundZoneEndOverlap);

    GroundZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    GroundZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GroundZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);

    GroundZone->SetBoxExtent(FVector{
        GroundAttackZoneRadius,
        GroundAttackZoneRadius,
        GroundZoneHeightRatio * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()
    });
    GroundZone->SetRelativeLocation(FVector{0.f, 0.f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()});

    ExternChocWaveZone = CreateDefaultSubobject<USphereComponent>("ExternChocWaveZone");
    ExternChocWaveZone->SetupAttachment(GetCapsuleComponent());
    ExternChocWaveZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ExternChocWaveZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    ExternChocWaveZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    ExternChocWaveZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    ExternChocWaveZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Overlap);

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
    BoxWeapon->OnComponentBeginOverlap.AddDynamic(this, &ABaseBoss::OnHandsObjectsBeginOverlap);
    BoxWeapon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    BoxWeapon->SetCollisionObjectType(COLLISION_CHANNEL_ENEMY);
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
    BoxShield->OnComponentBeginOverlap.AddDynamic(this, &ABaseBoss::OnHandsObjectsBeginOverlap);
    BoxShield->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    BoxShield->SetCollisionObjectType(COLLISION_CHANNEL_ENEMY);
    BoxShield->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH, ECollisionResponse::ECR_Ignore);
    BoxShield->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

    bIsPushable      = false;
    bIsEjectOnCharge = false;
    bIsEjectOnAttack = false;
}

void ABaseBoss::Punch() noexcept
{
    bAttacking = true;
    PlayAnimMontage(PunchAttack, PunchSpeed);
    OnPunch.Broadcast();
}

void ABaseBoss::GroundAttack() noexcept
{
    bAttacking = true;
    PlayAnimMontage(GroundAttackAnimMontage, PunchSpeed);
    OnGroundAttack.Broadcast();
}

void ABaseBoss::FireBallAttack() noexcept
{
    bAttacking = true;
    PlayAnimMontage(FireBallAttackSpeedAnimMontage, FireBallAttackSpeed);
    OnFireBallAttackBegin.Broadcast();
}

void ABaseBoss::ThrowFireBall() noexcept
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner                          = nullptr;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    FVector SpawnLocation = GetMesh()->GetBoneLocation(FireBallSpawningBoneName, EBoneSpaces::WorldSpace) + GetActorForwardVector() * 100.f;

    FVector  PlayerLoc            = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
    FRotator RotationTowardPlayer = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, PlayerLoc);

    AFireBall* NewFireBall = GetWorld()->SpawnActor<AFireBall>(FireBallType.Get(), SpawnLocation, RotationTowardPlayer,
                                                              SpawnParams);

    if (NewFireBall)
    {
        NewFireBall->SetDamage(FireBallDamage);
        NewFireBall->SetRadius(FireBallScale * 32.f);
        NewFireBall->SetActorScale3D(FVector{FireBallScale});
        NewFireBall->Throw(FireBallVelocity);
        OnFireBallThrow.Broadcast();
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("NewFireBall null"));
    }
}

void ABaseBoss::DoChocWave() noexcept
{
    bAttacking = true;

    TArray<AActor*> pActorsOverllapingWithChocWave;

    ExternChocWaveZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ExternChocWaveZone->GetOverlappingActors(pActorsOverllapingWithChocWave, ABaseCharacter::StaticClass());
    ExternChocWaveZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    for (AActor* pActor : pActorsOverllapingWithChocWave)
    {        
        ABaseCharacter* pCharacter = Cast<ABaseCharacter>(pActor);

        FVector LaunchForce = pActor->GetActorLocation() - GetActorLocation();
        const float ChocForceWithDistance = GroundAttackChocForce * (ChocForceDependingOfDistance ? 1.f : 1.f - (LaunchForce
        .SizeSquared() / (ExternChocWaveZone->GetScaledSphereRadius() * ExternChocWaveZone->GetScaledSphereRadius())));
        LaunchForce.Normalize();
        LaunchForce *= ChocForceWithDistance;
        LaunchForce.Z = GroundAttackChocForceHeightRatio * ChocForceWithDistance;

        ABasePlayer* pPlayer = Cast<ABasePlayer>(pActor);

        if (pPlayer)
        {
            pPlayer->TakeDamageCharacter(Damage);
        }

        pCharacter->LaunchAndStun(LaunchForce, true, true);
    }

    OnChocWave.Broadcast();
}

void ABaseBoss::SetLevel(uint8 NewLevel) noexcept
{
    Level = NewLevel;

    switch (Level) /*Cannot be reverse for optimize line numbers. Lower level must be execute before upper level*/
    {
        case 0:
            OnUpgradLevel1.Broadcast(Level);
            break;
            
        case 1:
            OnUpgradLevel1.Broadcast(Level);
            OnUpgradLevel2.Broadcast(Level);
        break;

        case 2:
            OnUpgradLevel1.Broadcast(Level);
            OnUpgradLevel2.Broadcast(Level);
            OnUpgradLevel3.Broadcast(Level);
        break;

        case 3:
            OnUpgradLevel1.Broadcast(Level);
            OnUpgradLevel2.Broadcast(Level);
            OnUpgradLevel3.Broadcast(Level);
            OnUpgradLevel4.Broadcast(Level);
        break;

        case 4:
            OnUpgradLevel1.Broadcast(Level);
            OnUpgradLevel2.Broadcast(Level);
            OnUpgradLevel3.Broadcast(Level);
            OnUpgradLevel4.Broadcast(Level);
            OnUpgradLevel5.Broadcast(Level);
        break;

        default: ;
    }
}

void ABaseBoss::BeginPlay()
{
    Super::BeginPlay();

    PunchZone->SetSphereRadius(PunchZoneRadius);
    BellyZone->SetBoxExtent(FVector{
        PunchZoneRadius,
        PunchZoneRadius,
        BellyZoneHeightRatio * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()
    });

    GroundAttackZone->SetSphereRadius(GroundAttackZoneRadius);
    GroundZone->SetBoxExtent(FVector{
        GroundAttackZoneRadius,
        GroundAttackZoneRadius,
        GroundZoneHeightRatio * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()
    });
    GroundZone->SetRelativeLocation(FVector{0.f, 0.f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()});

    //SetLevel(Cast<ABasePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->GetPlayerLevel());
}
