// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "TrashEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunPlayerActionSignature);

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ATrashEnemy : public ABaseEnemy
{
    GENERATED_BODY()

public :

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Attack)
    class UAnimMontage* Attack;

protected :

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Attack)
    bool bCanEjectPlayer = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta=(EditCondition="bCanEjectPlayer"))
    float WeaponShootForce = 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta=(EditCondition="bCanEjectPlayer"))
    float WeaponShootHeigthRatio = 1.f;

    UPROPERTY(BlueprintAssignable)
    FOnStunPlayerActionSignature OnStunPlayer;
    
public:

    ATrashEnemy();

    virtual void Kill() override;

protected:

    virtual void OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult&    SweepResult) override;
};
