// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireBall.h"
#include "ExplosiveFireBall.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireBallChocWaveActionSignature);

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API AExplosiveFireBall : public AFireBall
{
    GENERATED_BODY()

protected :
    
    UPROPERTY(EditAnywhere, Category= "ChocWave")
    class USphereComponent* ChocWaveZone;

    UPROPERTY(BlueprintAssignable)
    FOnFireBallChocWaveActionSignature OnChocWave;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "ChocWave")
    float ChocForce = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "ChocWave")
    float ChocForceHeightRatio = 1.f;
    
protected :

    virtual void OnFireBallBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                        const FHitResult&    SweepResult) override;

public :

    AExplosiveFireBall();
};
