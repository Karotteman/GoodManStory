// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "PlayerLevelUpgrade.generated.h"

USTRUCT(BlueprintType)
struct FPlayerLevelUpgrade : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	/**
	 * @brief Zone index in ZoneContainer. -1 for no zone
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0", UIMax = "100.0"))
    float RageRateToUnlockLevel = 0;

	UPROPERTY(EditAnywhere)
	bool bChangeStats = false;

	/*UPROPERTY(EditAnywhere, meta=(EditCondition="bChangeStats"))
	struct FPlayerStats
	{
		UPROPERTY(EditAnywhere)
		bool bChangeLife = false;
	
	};*/
	
	UPROPERTY(EditAnywhere)
	bool bChangeSkills = false;
	
	/*UPROPERTY(EditAnywhere, meta=(EditCondition="bChangeSkills"))
	struct FPlayerSkills
	{
		UPROPERTY(EditAnywhere)
		bool bAddSkills = false;
	};*/
};