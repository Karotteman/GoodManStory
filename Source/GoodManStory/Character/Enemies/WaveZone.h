// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveZone.generated.h"

UCLASS()
class GOODMANSTORY_API AWaveZone : public AActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere)
    class UShapeComponent* Collider;

public:
    // Sets default values for this actor's properties
    AWaveZone();

    virtual void BeginPlay() override;

public:

    /**
     * @brief Check if player with index 0 is overlaping in this zone
     * @return 
     */
    bool IsPlayerOnThisZone();
};
