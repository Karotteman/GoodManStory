// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMesh.h"

#include "PlayerStats.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GOODMANSTORY_API UPlayerStats : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};
