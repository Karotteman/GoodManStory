// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"

#include "TimerManager.h"
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

void ABaseCharacter::Destroyed()
{
	Super::Destroyed();

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

void ABaseCharacter::SetMaxLifeAndAddLifeDiff(float NewMaxLife)
{
	float DiffMaxLife = NewMaxLife - LifeMax;
	LifeMax = NewMaxLife;
	Life += DiffMaxLife;
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

void ABaseCharacter::LaunchAndStun(const FVector& Force, bool bXYOverride, bool bZOverride)
{
	/*If enemie is stun no not lunch*/
	if (bIsStun)
		return;
	
	LaunchCharacter(Force, bXYOverride, bZOverride);

	if (IsStunable())
		SetIsStun(true);
}

void ABaseCharacter::StartStunRecovery() noexcept
{
	FTimerHandle UnusedHandle;
	FTimerDelegate TimerDel;

	//Binding the function with specific values
	TimerDel.BindUFunction(this, FName("SetIsStun"), false);
	
	GetWorldTimerManager().SetTimer(
        UnusedHandle, TimerDel, StunRecoveryDelay, false);

}

void ABaseCharacter::Kill()
{
	bIsDead = true;
	OnCharacterDeath.Broadcast(this);
}