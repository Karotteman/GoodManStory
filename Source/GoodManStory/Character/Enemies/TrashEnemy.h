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

public:

    ATrashEnemy();

protected:

    virtual void OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                      const FHitResult&    SweepResult) override;

public:

    virtual void Kill() override;
};
