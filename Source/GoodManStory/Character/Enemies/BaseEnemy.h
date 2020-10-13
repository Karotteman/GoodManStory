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

    UPROPERTY(Category = Stats, EditAnywhere)
    float TimeToNextAttack = 3.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float RangeAttack = 100.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float ForceEjection = 300.f;



    UPROPERTY(Category = Stats, EditAnywhere,meta=(EditCondition="bRandomSize"))
    float SizeMin = 1.f;

    UPROPERTY(Category = Stats, EditAnywhere,meta=(EditCondition="bRandomSize"))
    float SizeMax = 1.f;

    UPROPERTY(Category = Stats, EditAnywhere,meta=(EditCondition="!bRandomSize"))
    float Size = 1.f;


public:

    UPROPERTY(Category=Stats, EditAnywhere, AdvancedDisplay)
    bool bRandomSize = false;
    
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

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetTimeToNextAttack() const noexcept { return TimeToNextAttack; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetRangeAttack() const noexcept { return RangeAttack; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GeForceEjection() const noexcept { return ForceEjection; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetSizeMin() const noexcept { return SizeMin; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetSizeMax() const noexcept { return SizeMax; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetSize() const noexcept { return Size; }

protected:
};
