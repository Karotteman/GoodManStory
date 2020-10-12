// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Templates/SubclassOf.h"

#include "SpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseEnemy> EnemyType = nullptr;
	
	UPROPERTY(EditAnywhere)
    int EnemyNumber = 0;

	/**
	 * @brief Interval between two spawn in second
	 */
	UPROPERTY(EditAnywhere)
	float SpawnIntervalDelay = 0.5f;
	
	/**
	 * @brief Delay before the first spawn. By default 0 for no waiting time. In second
	 */
	UPROPERTY(EditAnywhere)
	float FirstSpawnDelayOffset = 0.f;

	/**
	* @brief Spawning radius arround spawner. If many mob must be spawn in same time, please define radius to avoid entity fusion
	*/
	UPROPERTY(EditAnywhere)
	float SpawnRadius = 0.f;

	/**
	* @brief Spawn index in SpawnContainer. -1 for random spawner
	*/
	UPROPERTY(EditAnywhere)
	int SpawnerID = -1;
};