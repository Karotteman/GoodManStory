// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaveEvent.generated.h"

class UWaveEvent;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnWaveStartSignature, UWaveEvent, OnWaveBegin);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnWaveEndSignature, UWaveEvent, OnWaveEnd);

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API UWaveEvent : public UObject
{
	GENERATED_BODY()

	public :
	
	UPROPERTY(BlueprintAssignable)
	FOnWaveStartSignature OnWaveBegin;

	UPROPERTY(BlueprintAssignable)
	FOnWaveEndSignature OnWaveEnd;
};
