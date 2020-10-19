// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"

#include "EnemyState.generated.h"

USTRUCT(BlueprintType)
struct FEnemyState
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseEnemy> Type;

	UPROPERTY(EditAnywhere)
	uint16 MaxNumberOnScene;

	UPROPERTY(VisibleAnywhere)
	TArray<class ABaseEnemy*> LivingEnemyContainer;
};