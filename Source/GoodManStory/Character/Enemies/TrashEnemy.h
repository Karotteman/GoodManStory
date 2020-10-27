// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "TrashEnemy.generated.h"

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
    
public:

    ATrashEnemy();

    virtual void Kill() override;
    
protected:

    virtual void OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                      const FHitResult&    SweepResult) override;
};
