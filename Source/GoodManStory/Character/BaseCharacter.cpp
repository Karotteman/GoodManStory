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
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::TakeLife(uint8 AdditionnalLife) noexcept
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

void ABaseCharacter::TakeDammage(uint8 Dammage) noexcept
{	
	if ((int8)Life - Dammage <= 0)
	{
		/*Kill*/
	}
	else
	{
		Life -= Dammage;
	}
}