// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABaseEnemy : public ABaseCharacter
{
    GENERATED_BODY()

    UPROPERTY(Category = Stats, EditAnywhere)
    float RageRewardOnKill = 10.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float MinAvoidanceRadius = 100.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float MaxAvoidanceRadius = 1000.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float AvoidanceLimitDistance = 1000.f;

public:
    
    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetMinAvoidanceRadius() const noexcept { return MinAvoidanceRadius; }
    
    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetMaxAvoidanceRadius() const noexcept { return MaxAvoidanceRadius; }
    
    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetAvoidanceLimitDistance() const noexcept { return AvoidanceLimitDistance; }
    
    ABaseEnemy();
    virtual void Kill() override;

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetRageRewardOnKill() const noexcept { return RageRewardOnKill; }

protected:
    
};
