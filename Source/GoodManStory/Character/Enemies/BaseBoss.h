// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseEnemy.h"
#include "BaseBoss.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABaseBoss : public ABaseEnemy
{
    GENERATED_BODY()

protected :

    UPROPERTY(EditAnywhere)
    class USphereComponent* PunchZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"))
    float PunchZoneRadius = 1000.f;

    UPROPERTY(EditAnywhere)
    class UBoxComponent* BellyZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0", UIMax = "1.0"))
    float BellyZoneHeightRatio = 0.3f;

    /**
     * @brief In second
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"))
    float PunchCooldown = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnBellyZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnPunchZone;

protected :

    virtual void OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult&    SweepResult) override;

    UFUNCTION()
    void OnBellyZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                 const FHitResult&    SweepResult);

    UFUNCTION()
    void OnBellyZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32                OtherBodyIndex);

    UFUNCTION()
    void OnPunchZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                 const FHitResult&    SweepResult);

    UFUNCTION()
    void OnPunchZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32                OtherBodyIndex);

public :

    ABaseBoss();

protected:
    virtual void BeginPlay() override;
};
