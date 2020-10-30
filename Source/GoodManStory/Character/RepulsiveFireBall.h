// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplosiveFireBall.h"
#include "RepulsiveFireBall.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ARepulsiveFireBall : public AExplosiveFireBall
{
	GENERATED_BODY()

	protected :

    virtual void OnFireBallBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                        const FHitResult&    SweepResult) override;

	UFUNCTION()
	void OnChocWaveZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                    const FHitResult&    SweepResult);

	public :

        ARepulsiveFireBall();
	
};
