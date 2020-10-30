// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Life = LifeMax;
	
	Super::BeginPlay();
	OnCharacterSpawn.Broadcast();
}

void ABaseCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	OnCharacterIsDestroy.Broadcast();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::TakeDamageCharacter(float dmg) noexcept
{	
	if (Life - dmg <= 0.f)
	{
		Life = 0.f;
		OnCharacterTakeDamage.Broadcast(this, dmg, dmg - Life);
		Kill();
	}
	else
	{
		Life -= dmg;
		OnCharacterTakeDamage.Broadcast(this, dmg, dmg);
	}
}

void ABaseCharacter::TakeLife(float AdditionnalLife) noexcept
{
	if (Life + AdditionnalLife > LifeMax)
	{
		Life = LifeMax;
		OnCharacterTakeLife.Broadcast(this, AdditionnalLife, AdditionnalLife - Life);
	}
	else
	{
		Life += AdditionnalLife;
		OnCharacterTakeLife.Broadcast(this, AdditionnalLife, AdditionnalLife);
	}
}

void ABaseCharacter::Kill()
{
	bIsDead = true;
	OnCharacterDeath.Broadcast(this);
}

void ABaseCharacter::Launch(const FVector& Direction, float Force, bool bXYOverride, bool bZOverride)
{
	LaunchCharacter(Direction * Force, bXYOverride, bZOverride);
}

void ABaseCharacter::Expelled(const FVector& Direction, float Force, bool bXYOverride, bool bZOverride)
{
	LaunchCharacter(Direction * Force, bXYOverride, bZOverride);
	bIsExpelled = true;
}