// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoodManStory/Character/BaseWarrior.h"
#include "BaseEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamageOnWeakZoneActionSignature);

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABaseEnemy : public ABaseWarrior
{
    GENERATED_BODY()

protected :

    UPROPERTY(Category = Stats, EditAnywhere)
    float RageRewardOnKill = 10.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float MinAvoidanceRadius = 100.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float MaxAvoidanceRadius = 1000.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float AvoidanceLimitDistance = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float TimeToNextAttack = 3.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    float RangeAttack = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
    bool bIsEjectOnAttack = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
    bool bIsEjectOnCharge = true;

    UPROPERTY(Category = Stats, EditAnywhere,meta=(EditCondition="bRandomSize"))
    float SizeMin = 1.f;

    UPROPERTY(Category = Stats, EditAnywhere,meta=(EditCondition="bRandomSize"))
    float SizeMax = 1.f;

    UPROPERTY(Category = Stats, EditAnywhere,meta=(EditCondition="!bRandomSize"))
    float Size = 1.f;
    
    UPROPERTY(Category = Stats, EditAnywhere)
    float ReducingTimePlayerSkillsRewardOnKill = 1.f;

    UPROPERTY(BlueprintAssignable)
    FOnTakeDamageOnWeakZoneActionSignature OnTakeDamageOnWeakZone;
    
public:

    UPROPERTY(Category = Stats, EditAnywhere, meta=(EditCondition="bIsEjectOnCharge"))
    float ForceChargeEjection = 150.f;

    UPROPERTY(Category = Stats, EditAnywhere, meta=(EditCondition="bIsEjectOnAttack"))
    float ForceEjection = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
    bool bAttacking = false;

    UPROPERTY(EditAnywhere, Category=Stats, AdvancedDisplay)
    bool bRandomSize = false;

    UPROPERTY(EditAnywhere, Category=Stats, AdvancedDisplay)
    bool bIsPushable = false;

public:

    ABaseEnemy();

    virtual void Kill() override;

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE bool IsPushable() const noexcept { return bIsPushable; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetMinAvoidanceRadius() const noexcept { return MinAvoidanceRadius; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetMaxAvoidanceRadius() const noexcept { return MaxAvoidanceRadius; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetAvoidanceLimitDistance() const noexcept { return AvoidanceLimitDistance; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetRageRewardOnKill() const noexcept { return RageRewardOnKill; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetScoreRewardOnKill() const noexcept { return RageRewardOnKill + LifeMax; }

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

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetReducingTimePlayerSkillsRewardOnKill() const { return ReducingTimePlayerSkillsRewardOnKill; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetReducingTimePlayerSkillsRewardOnKill(float NewReducingTimePlayerSkillsRewardOnKill)
    {
        ReducingTimePlayerSkillsRewardOnKill = NewReducingTimePlayerSkillsRewardOnKill;
    }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE bool IsEjectOnAttack() const { return bIsEjectOnAttack; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void TakeDamageOnWeakZone() { OnTakeDamageOnWeakZone.Broadcast(); }
    
    UFUNCTION(Category = Stats)
    void SetIsEjectOnAttack(bool NewIsEjectOnAttack) { bIsEjectOnAttack = NewIsEjectOnAttack; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE bool IsEjectOnCharge() const { return bIsEjectOnCharge; }

    UFUNCTION(Category = Stats)
    void SetIsEjectOnCharge(bool NewIsEjectOnCharge) { bIsEjectOnCharge = NewIsEjectOnCharge; }

    virtual void SetIsStun(bool bNewStun) noexcept override;
    
};
