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

	UPROPERTY(VisibleAnywhere)
	int EnemyCounter = EnemyNumber;

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

	UPROPERTY(VisibleAnywhere, meta=(EditCondition="FirstSpawnDelayOffset > 0.f"))
	bool bWaitOffset = true; //Use for the offset
	
	/**
	* @brief Spawning radius arround spawner. If many mob must be spawn in same time, please define radius to avoid entity fusion
	*/
	UPROPERTY(EditAnywhere)
	float SpawnRadius = 0.f;

	/**
	* @brief Spawns index in SpawnContainer. If multiple spawner is enter, random spawner is choose on the list
	*/
	UPROPERTY(EditAnywhere)
	TArray<uint16> SpawnersID;

	float TimeCount = 0.f;
};