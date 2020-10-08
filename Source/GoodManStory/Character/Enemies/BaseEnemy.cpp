// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Components/SkeletalMeshComponent.h"


ABaseEnemy::ABaseEnemy()
{
}

void ABaseEnemy::Dead()
{
    GetMesh()->SetVisibility(false);
}
