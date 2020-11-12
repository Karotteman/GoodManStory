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

    /*SocketOffSet interpolation*/
    FTimeline TimeLineSocketOffSet;
    FVector   StartPositionSocketOffSet;
    FVector   EndPositionSocketOffSet;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SocketOffSetInterpolationSetting, meta = (AllowPrivateAccess = "true"))
    float FPlayRateSocketOffSetInterpolation = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SocketOffSetInterpolationSetting, meta = (AllowPrivateAccess = "true"))
    float FCameraSholderOffset = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SocketOffSetInterpolationSetting, meta = (AllowPrivateAccess = "true"))
    UCurveFloat* CurveSocketOffSet;

    /*ArmLength interpolation*/
    FTimeline TimeLineSocketArmLength;    
    float     FStartPositionSocketArmLength;
    float     FEndPositionSocketArmLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArmLengthInterpolationSetting, meta = (AllowPrivateAccess = 
    "true"))
    float     FBaseArmLength;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ArmLengthInterpolationSetting, meta = (AllowPrivateAccess = 
    "true"))
    float FPlayRateSocketArmLengthInterpolation = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ArmLengthInterpolationSetting, meta = (AllowPrivateAccess = 
    "true"))
    float FCameraSholderArmLength = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ArmLengthInterpolationSetting, meta = (AllowPrivateAccess = 
    "true"))
    UCurveFloat* CurveSocketArmLength;

public :

    UCharacterCameraBoom();

    UFUNCTION(BlueprintCallable)
    void InterpolateOffSet(FVector NewPosition);

    /**
     * @brief move forward or back ward the camera
     * @param FScale : scale with baseArmLength. 1.0f reset the arm length
     */
    UFUNCTION(BlueprintCallable)
    void InterpolateArmLength(float FScale);

    /**
    * @brief Update interpolation
    */
    UFUNCTION()
    void Update(float FDeltaTime);

    UFUNCTION(BlueprintCallable)
    void InvertCameraSholder();

private:

    UFUNCTION()
    void InitOffSetInterpolationTimeLine() noexcept;

    UFUNCTION(BlueprintCallable)
    void SetNewArmLength(float NewArmLength) noexcept;

    UFUNCTION()
    void InitArmLengthInterpolationTimeLine() noexcept;

    UFUNCTION(BlueprintCallable)
    void InterpolateOffSetProgress(float FValue);

    UFUNCTION(BlueprintCallable)
    void InterpolateArmLengthProgress(float FValue);
};
