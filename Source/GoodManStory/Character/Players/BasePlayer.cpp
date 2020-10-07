// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"


// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "TimerManager.h" // FTimerManager::SetTimer
#include "GameFramework/CharacterMovementComponent.h" //UCharacterMovementComponent::SetMovementMode
#include "Components/SkeletalMeshComponent.h" //USkeletalMeshComponent
#include "Components/PrimitiveComponent.h" //OnComponentOverlap
#include "Engine/EngineTypes.h" //FHitResult
#include "Materials/Material.h"//SetMaterial, GetMaterial
#include "Materials/MaterialInstanceDynamic.h" //SetVectorParameterValue, UMaterialInstanceDynamic
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
/*Debug*/
#include "Engine/GameEngine.h" //AddOnScreenDebugMessage
#include "Containers/UnrealString.h"

//////////////////////////////////////////////////////////////////////////
// AGladiatorUE4Character

ABasePlayer::ABasePlayer()
{
    // set our turn rates for input
    BaseTurnRate   = 45.f;
    BaseLookUpRate = 45.f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength         = 300.0f; // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true;   // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(GetMesh(), "weaponShield_l");

    BoxWeapon = CreateDefaultSubobject<UBoxComponent>("BoxWeapon");
    BoxWeapon->SetupAttachment(Weapon);
    BoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
    PlayerInputComponent->BindAction("EvilSpellCapcity", IE_Pressed, this, &ABasePlayer::EvilSpellCapcity);
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
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Charge"));
}

void ABasePlayer::BasicAttack()
{
    if (bCanAttack)
    {
        bAttacking = true;
        bCanAttack = false;
        PlayAnimMontage(SlotAnimationsAttackCombo[BasicAttackComboCount]);

        if (BasicAttackComboCount >= SlotAnimationsAttackCombo.Num() - 1)
            BasicAttackComboCount = 0;
        else
            BasicAttackComboCount++;
    }

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
                                         "BasicAttack combo:" + FString::FromInt(BasicAttackComboCount));
}

void ABasePlayer::TourbilolAttack()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("TourbilolAttack"));
}

void ABasePlayer::EvilSpellAttack()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("EvilSpellAttack"));
}

void ABasePlayer::EvilSpellCapcity()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("EvilSpellCapcity"));
}

void ABasePlayer::SwitchCameraMode()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("SwitchCameraMode"));
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
    BasicAttackComboCount = 0;
    bCanAttack             = false;
    bAttacking             = false;
}

void ABasePlayer::SetCanAttack(bool canAttack)
{
    bCanAttack = canAttack;
}

void ABasePlayer::AttackActiveHitBox(bool isActive)
{
    if (isActive)
        BoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    else
        BoxWeapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
