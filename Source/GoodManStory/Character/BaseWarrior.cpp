// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWarrior.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ABaseWarrior::ABaseWarrior()
{}

void ABaseWarrior::AttackActiveHitBox(bool bIsActive, UBoxComponent* BoxWeapon)
{
	if (bIsActive)
		BoxWeapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
		BoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
