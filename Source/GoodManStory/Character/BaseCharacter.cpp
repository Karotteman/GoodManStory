// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Life = LifeMax;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::TakeDammage(float Dammage) noexcept
{	
	if (Life - Dammage <= 0.f)
	{
		Life = 0.f;
		Kill();
	}
	else
	{
		Life -= Dammage;
	}
}

void ABaseCharacter::TakeLife(float AdditionnalLife) noexcept
{
	if (Life + AdditionnalLife > LifeMax)
	{
		Life = LifeMax;
	}
	else
	{
		Life += AdditionnalLife;
	}
}


void ABaseCharacter::Kill()
{
	bIsDead = true;
}
