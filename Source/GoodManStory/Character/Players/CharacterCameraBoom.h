// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/TimelineComponent.h"

#include "CharacterCameraBoom.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API UCharacterCameraBoom : public USpringArmComponent
{
    GENERATED_BODY()

protected:

    FTimeline    TimeLine;
    FVector      StartPosition;
    FVector      EndPosition;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
    float FPlayRateCameraTransition = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
    float FCameraSholderOffset = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
    UCurveFloat* Curve;
    
public :

    UCharacterCameraBoom();

    UFUNCTION(BlueprintCallable)
    void InterpolatePosition(FVector NewPosition);

    /**
    * @brief Update interpolation
    */
    UFUNCTION()
    void Update(float FDeltaTime);

    UFUNCTION(BlueprintCallable)
    void InvertCameraSholder();

private:

    UFUNCTION(BlueprintCallable)
    void SwitchCameraModeProgress(float FValue);
};
