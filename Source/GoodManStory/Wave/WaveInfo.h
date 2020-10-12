// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnInfo.h"
#include "Engine/DataTable.h"

#include "WaveInfo.generated.h"

USTRUCT(BlueprintType)
struct FWaveInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief Zone index in ZoneContenor. -1 for no zone
	 */
	UPROPERTY(EditAnywhere)
    int Zone = -1;

	UPROPERTY(EditAnywhere)
	TArray<FSpawnInfo> SpawninfoContenor;
};