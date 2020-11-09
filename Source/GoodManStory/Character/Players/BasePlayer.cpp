// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayer.h"


// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h" // FTimerManager::SetTimer
#include "Components/SkeletalMeshComponent.h" //USkeletalMeshComponent
#include "Components/PrimitiveComponent.h" //OnComponentOverlap
#include "Engine/EngineTypes.h" //FHitResult
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "CharacterCameraBoom.h"
#include "Engine/Engine.h"
#include "AIController.h"
#include "../Enemies/BaseEnemy.h"
#include "GoodManStory/Character/MonoHitBehaviours.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

/*Debug*/
#include <Utility/Utility.h>
#include "Containers/UnrealString.h"
#include "Kismet/KismetSystemLibrary.h"


#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1
#define COLLISION_CHANNEL_TRASH_MOB ECC_GameTraceChannel2
#define COLLISION_CHANNEL_ENEMY ECC_GameTraceChannel3

//////////////////////////////////////////////////////////////////////////
// AGladiatorUE4Character

ABasePlayer::ABasePlayer()
{
    bAllowTickBeforeBeginPlay = false;
    // set our turn rates for input
    BaseTurnRate   = 45.f;
    BaseLookUpRate = 45.f;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw   = false;
    bUseControllerRotationRoll  = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate              = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity             = 600.f;
    GetCharacterMovement()->AirControl                = 0.2f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<UCharacterCameraBoom>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength         = 300.0f; // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true;   // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, UCharacterCameraBoom::SocketName);
    // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    GetMesh()->SetRelativeLocation({0.f, 0.f, -80.f});
    GetMesh()->SetRelativeRotation({0.f, 0.f, -90.f});
    GetMesh()->SetCollisionProfileName(FName{"NoCollision"});
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    GetCapsuleComponent()->SetCollisionObjectType(COLLISION_CHANNEL_PLAYER);
    GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH_MOB, ECollisionResponse::ECR_Overlap);

    LeftHandObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
    LeftHandObject->SetupAttachment(GetMesh(), "hand_l");
    LeftHandObject->SetRelativeScale3D({1.5f, 1.5f, 1.f});
    LeftHandObject->SetRelativeRotation({0.f, 0.f, 20.f});
    LeftHandObject->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    LeftHandObject->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    LeftHandObject->SetCollisionResponseToChannel(COLLISION_CHANNEL_TRASH_MOB, ECollisionResponse::ECR_Overlap);
    LeftHandObject->SetCollisionResponseToChannel(COLLISION_CHANNEL_ENEMY, ECollisionResponse::ECR_Overlap);

    BoxWeapon = CreateDefaultSubobject<UBoxComponent>("BoxWeapon");
    BoxWeapon->SetupAttachment(LeftHandObject);
    BoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BoxWeapon->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::OnRightHandObjectBeginOverlap);
    BoxWeapon->SetCollisionObjectType(COLLISION_CHANNEL_PLAYER);
    BoxWeapon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    BoxWeapon->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Ignore);
    BoxWeapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    BoxWeapon->SetRelativeLocation({0.f, 70.f, 0.f});
    BoxWeapon->SetRelativeScale3D({1.f, 0.8f, 0.5f});

    SphericChargeZone = CreateDefaultSubobject<USphereComponent>("SphericChargeZone");
    SphericChargeZone->SetupAttachment(GetMesh());
    SphericChargeZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SphericChargeZone->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::OnChargeBeginOverlap);
    SphericChargeZone->SetCollisionObjectType(COLLISION_CHANNEL_PLAYER);
    SphericChargeZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SphericChargeZone->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Ignore);
    SphericChargeZone->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    SphericChargeZone->SetRelativeScale3D({1.5f, 1.5f, 1.5f});

    MonoHitBehavioursComponent = CreateDefaultSubobject<UMonoHitBehaviours>(TEXT("MonoHitBehavioursComponent"));

    bIsStunable = false;
    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);

    //Bind keys inputs actions
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAction("Charge", IE_Pressed, this, &ABasePlayer::Charge);
    PlayerInputComponent->BindAction("BasicAttack", IE_Pressed, this, &ABasePlayer::BasicAttack);
    PlayerInputComponent->BindAction("TourbilolAttack", IE_Pressed, this, &ABasePlayer::TourbilolAttack);
    PlayerInputComponent->BindAction("EvilSpellAttack", IE_Pressed, this, &ABasePlayer::EvilSpellAttack);
    PlayerInputComponent->BindAction("EvilSpellCapcity", IE_Pressed, this, &ABasePlayer::EvilSpellCapacity);
    PlayerInputComponent->BindAction("SwitchCameraMode", IE_Pressed, this, &ABasePlayer::SwitchCameraMode);

    //Bind axis inputs actions
    PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &ABasePlayer::LookUpAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    //PlayerInputComponent->BindAxis("LookUpRate", this, &ABasePlayer::TurnAtRate);
}

void ABasePlayer::Charge()
{
    if (GetCharacterMovement()->IsFalling() || !bCanDoAction)
        return;

    bCanDoAction = false;
    bCanAttack = false;
    
    /*Play animation and activate/Desactivate collider*/
    PlayAnimMontage(SlotAnimationsCharge);

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Charge"));
}

void ABasePlayer::BasicAttack()
{    
    if (!bCanAttack && !bCanDoAction)
        return;

    bCanDoAction = false;
    bCanAttack = false;
    
    PlayAnimMontage(SlotAnimationsAttackCombo[BasicAttackComboCount], BasicAttackSpeed);
    MonoHitBehavioursComponent->Reset();

    OnPlayerBeginBasicAttack.Broadcast(BasicAttackComboCount);
    
    if (BasicAttackComboCount >= SlotAnimationsAttackCombo.Num() - 1)
        BasicAttackComboCount = 0;
    else
        BasicAttackComboCount++;
    
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
                                         "BasicAttack combo:" + FString::FromInt(BasicAttackComboCount));
}

void ABasePlayer::TourbilolAttack()
{
    if (!bTourbillolIsUnlock || !bCanDoAction)
        return;

    bCanDoAction = false;
    bCanAttack = false;
    bDoTourbilol = true;
    
    PlayAnimMontage(SlotAnimationsTourbillol);
    
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("TourbilolAttack"));
}

void ABasePlayer::EvilSpellAttack()
{
    /*if (!bEvilSpellAttackIsUnlock)
        return;*/

    //if (GEngine)
    //    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("EvilSpellAttack"));
}

void ABasePlayer::EvilSpellCapacity()
{
    if (!bEvilSpellCapacityIsUnlock)
        return;
    
    if (bCanEvilSpellCapacity)
    {
        bCanEvilSpellCapacity = false;
        UGameplayStatics::SetGlobalTimeDilation(GetWorld(), WorldSlowingSpeedEvil);
        CustomTimeDilation = 1 - WorldSlowingSpeedEvil + PlayerSlowingSpeedEvil + 2;
        GetWorldTimerManager().SetTimer(MemberTimerEvilCapacity, this, &ABasePlayer::SetCanEvilCapacity,
                                        DurationOfTheSlowdownEvil, false, 1);

        OnPlayerBeginEvilCapacity.Broadcast();
    }
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("EvilSpellCapcity"));
}


void ABasePlayer::EvilHealing()
{
    Life+= Heal;
}

void ABasePlayer::SetCanEvilCapacity()
{
    bCanEvilSpellCapacity = true;
    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
    CustomTimeDilation = 1;
    GetWorldTimerManager().ClearTimer(MemberTimerEvilCapacity);

    OnPlayerEndEvilCapacity.Broadcast();
}

void ABasePlayer::SwitchCameraMode()
{
    CameraBoom->InterpolateOffSet(FVector::ZeroVector);
    
    OnPlayerBeginSwitchCamera.Broadcast();
}

void ABasePlayer::MoveCameraArmLength(float FScale) noexcept
{
    CameraBoom->InterpolateArmLength(FScale);
}

void ABasePlayer::ResetCameraArmLength() noexcept
{
    CameraBoom->InterpolateArmLength(1.f);
}

void ABasePlayer::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABasePlayer::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABasePlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    CameraBoom->Update(DeltaTime);

    TArray<AActor*> othersOverllaping;
    GetCapsuleComponent()->GetOverlappingActors(othersOverllaping, ABaseEnemy::StaticClass());

    for (AActor* other : othersOverllaping)
    {
        Push(other);
    }
}

void ABasePlayer::MoveForward(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ABasePlayer::MoveRight(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

void ABasePlayer::ResetCombo()
{
    MonoHitBehavioursComponent->Reset();
    BasicAttackComboCount = 0;
    bCanAttack            = false;
}

void ABasePlayer::SetCanAttack(bool bNewCanAttack)
{
    bCanAttack = bNewCanAttack;
}

void ABasePlayer::OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult&    SweepResult)
{    
    if (OtherComp->ComponentHasTag("Body"))
    {        
        ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);

        if (UNLIKELY(!Enemy))
            return;

        /*Add the actor on if is has not already hit*/
        if (UNLIKELY(!bDoTourbilol && MonoHitBehavioursComponent->CheckIfAlreadyExistAndAdd(OtherActor)))
            return;
        
        if (UNLIKELY(OtherComp->ComponentHasTag(TEXT("CharacterWeakZone"))))
            Enemy->TakeDamageCharacter(Damage * WeakZoneDamageMultiplicator);
        else
            Enemy->TakeDamageCharacter(Damage);
            
        if (LIKELY(Enemy->IsEjectOnAttack()))
        {
            FVector LaunchForce = OtherActor->GetActorLocation() - OverlappedComp->GetComponentLocation();
            LaunchForce.Normalize();
            LaunchForce *= WeaponShootForce;
            LaunchForce.Z = WeaponShootHeigthRatio * WeaponShootForce;
            Enemy->GetMesh()->AddImpulse(LaunchForce, NAME_None, true);
        }

        if (LIKELY(Enemy->IsDead()))
        {
            AddScore(Enemy->GetScoreRewardOnKill());
            TakeRage(Enemy->GetRageRewardOnKill());
        }
    }
}

void ABasePlayer::TakeRage(float AdditionnalRage) noexcept
{
    if (Rage + AdditionnalRage > MaxRage)
    {
        Rage = MaxRage;
        OnPlayerTakeRage.Broadcast(Rage, AdditionnalRage, MaxRage - Rage);
    }
    else
    {
        Rage += AdditionnalRage;
        OnPlayerTakeRage.Broadcast(Rage, AdditionnalRage, AdditionnalRage);
    }
    
    float RageRate = Rage / MaxRage * 100.f;

    switch (Level)
    {
        case 0:
            if (RageRate < RageToUnlockLevel1)
                break;
            while (GetPlayerLevel() < 1)
                LevelUp();
        
        case 1:
            if (RageRate < RageToUnlockLevel2)
                break;
            while (GetPlayerLevel() < 2)
                LevelUp();
        case 2:
            if (RageRate < RageToUnlockLevel3)
                break;
            while (GetPlayerLevel() < 3)
                LevelUp();
        case 3:
            if (RageRate < RageToUnlockLevel4)
                break;
            while (GetPlayerLevel() < 4)
                LevelUp();
        case 4:
            if (RageRate < RageToUnlockLevel5)
                break;
            while (GetPlayerLevel() < 5)
                LevelUp();
        default: ;
    }
}

void ABasePlayer::LevelUp() noexcept
{
    if (Level + 1 > MaxLevel)
    {
        OnPlayerLevelUp.Broadcast(MaxLevel);
        return;
    }
    else
    {
        Level ++;
        OnPlayerLevelUp.Broadcast(Level);
    }

    switch (Level)
    {
        case 1:
            OnPlayerUpgradLevel1.Broadcast(Level);
            break;

        case 2:
            OnPlayerUpgradLevel2.Broadcast(Level);
            break;

        case 3:
            OnPlayerUpgradLevel3.Broadcast(Level);
            break;

        case 4:
            OnPlayerUpgradLevel4.Broadcast(Level);
            break;

        case 5:
            OnPlayerUpgradLevel5.Broadcast(Level);
            break;
        default: ;
    }
}

void ABasePlayer::OnChargeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                       const FHitResult&    SweepResult)
{
    if (OtherComp->ComponentHasTag("Body"))
    {
        ABaseEnemy* pEnemy = Cast<ABaseEnemy>(OtherActor);
        if (pEnemy && pEnemy->IsEjectOnCharge())
        {
            OnPlayerChargeHit.Broadcast(pEnemy);
            
            FVector LaunchForce = OtherActor->GetActorLocation() - GetActorLocation();
            LaunchForce.Normalize();
            LaunchForce *= pEnemy->ForceEjection;
            LaunchForce.Z = ChargeExpulseHeigthRatio * ChargeExpulseForce;

            pEnemy->LaunchAndStun(LaunchForce, true, true);
        }
    }
}

void ABasePlayer::Push(AActor* other)
{
    ABaseEnemy* pEnemy = Cast<ABaseEnemy>(other);
    if (pEnemy && pEnemy->IsPushable())
    {
        FVector Direction = other->GetActorLocation() - GetActorLocation();
        Direction.Normalize();
        Direction.Z = 0.f;

        //pEnemy->SetActorLocation(GetActorLocation() + Direction * (pEnemy->GetCapsuleComponent()->GetScaledCapsuleRadius() + 
        //GetCapsuleComponent()->GetScaledCapsuleRadius()));
        //pEnemy->GetCharacterMovement()->AddForce(Direction * PushForce);
        //pEnemy->GetCharacterMovement()->AddImpulse(Direction * PushForce, true);
        pEnemy->LaunchCharacter(Direction * PushForce, true, true);
    }
}

void ABasePlayer::ChargeActiveHitBox(bool bIsActive)
{
    if (bIsActive)
    {
        SphericChargeZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

        /*Dash*/
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
        GetCharacterMovement()->Velocity       = (GetActorForwardVector() * ChargeImpulsionForce);
        GetCharacterMovement()->GroundFriction = 0.f;
    }
    else
    {
        GetCharacterMovement()->GroundFriction = 8.f;
        GetCharacterMovement()->Velocity       = FVector::ZeroVector;
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
        SphericChargeZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ABasePlayer::Stopcharge()
{
    OnPlayerEndCharge.Broadcast();
}

void ABasePlayer::AddScore(int32 AdditionalScore) noexcept
{
    Score += AdditionalScore;
    OnPlayerTakeScore.Broadcast(Score, AdditionalScore);
}

void ABasePlayer::Kill()
{
    Super::Kill();

    Rage *= 1.f - LosingRageRatioOnDeath;
    Score *= 1.f - LosingScoreRatioOnDeath;
}
