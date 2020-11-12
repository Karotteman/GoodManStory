// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterCameraBoom.h"
#include "BasePlayer.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

UCharacterCameraBoom::UCharacterCameraBoom()
    : Super()
{
    SocketOffset            = FVector{0.f, FCameraSholderOffset, 0.f};
    TargetArmLength         = 300.0f; // The camera follows at this distance behind the character	
    bUsePawnControlRotation = true;   // Rotate the arm based on the controller

    InitOffSetInterpolationTimeLine();
    InitArmLengthInterpolationTimeLine();
}

void UCharacterCameraBoom::InterpolateOffSet(FVector NewPosition)
{
    StartPositionSocketOffSet = SocketOffset;
    EndPositionSocketOffSet   = NewPosition;

    if (TimeLineSocketOffSet.IsPlaying())
    {
        InvertCameraSholder();
    }

    TimeLineSocketOffSet.PlayFromStart();


    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("InterpolateOffSet"));
}

void UCharacterCameraBoom::InterpolateArmLength(float FScale)
{
    FStartPositionSocketArmLength = TargetArmLength;
    FEndPositionSocketArmLength   = FBaseArmLength * FScale;

    TimeLineSocketArmLength.PlayFromStart();

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("InterpolateArmLength"));
}

void UCharacterCameraBoom::InitOffSetInterpolationTimeLine() noexcept
{
    TimeLineSocketOffSet = FTimeline{};
    FOnTimelineFloat       progressFunction{};
    FOnTimelineEventStatic finishFunction{};

    progressFunction.BindUFunction(this, "InterpolateOffSetProgress");
    finishFunction.BindUFunction(this, "InvertCameraSholder");

    if (!CurveSocketOffSet)
    {
        const ConstructorHelpers::FObjectFinder<UCurveFloat> DefaultCurve(
            TEXT("CurveFloat'/Game/Assets/Curve/BasicBlendCurve.BasicBlendCurve'"));

        if (DefaultCurve.Object)
        {
            TimeLineSocketOffSet.AddInterpFloat(DefaultCurve.Object, progressFunction, FName{TEXT("BlendCamPos")});
        }
        else
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Cannot find curve"));
        }
    }
    else
    {
        TimeLineSocketOffSet.AddInterpFloat(CurveSocketOffSet, progressFunction, FName{TEXT("BlendCamPos")});
    }

    TimeLineSocketOffSet.SetTimelineFinishedFunc(finishFunction);
    TimeLineSocketOffSet.SetPlayRate(FPlayRateSocketOffSetInterpolation);
    TimeLineSocketOffSet.SetTimelineLength(1.f);
}

void UCharacterCameraBoom::SetNewArmLength(float NewArmLength) noexcept
{
    FBaseArmLength = NewArmLength;
    TargetArmLength = NewArmLength;
}

void UCharacterCameraBoom::InitArmLengthInterpolationTimeLine() noexcept
{
    TimeLineSocketArmLength = FTimeline{};
    FOnTimelineFloat progressFunction{};

    progressFunction.BindUFunction(this, "InterpolateArmLengthProgress");

    if (!CurveSocketArmLength)
    {
        const ConstructorHelpers::FObjectFinder<UCurveFloat> DefaultCurve(
            TEXT("CurveFloat'/Game/Assets/Curve/BasicBlendCurve.BasicBlendCurve'"));

        if (DefaultCurve.Object)
        {
            TimeLineSocketArmLength.AddInterpFloat(DefaultCurve.Object, progressFunction, FName{TEXT("BlendCamPos")});
        }
        else
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Cannot find curve"));
        }
    }
    else
    {
        TimeLineSocketArmLength.AddInterpFloat(CurveSocketArmLength, progressFunction, FName{TEXT("BlendCamPos")});
    }

    TimeLineSocketArmLength.SetPlayRate(FPlayRateSocketArmLengthInterpolation);
    TimeLineSocketArmLength.SetTimelineLength(1.f);
    FBaseArmLength = TargetArmLength;
}

void UCharacterCameraBoom::Update(float FDeltaTime)
{
    if (TimeLineSocketOffSet.IsPlaying())
    {
        TimeLineSocketOffSet.TickTimeline(FDeltaTime);
    }

    if (TimeLineSocketArmLength.IsPlaying())
    {
        TimeLineSocketArmLength.TickTimeline(FDeltaTime);
    }
}

void UCharacterCameraBoom::InterpolateOffSetProgress(float FValue)
{
    //TODO: Can be replace by end position
    SocketOffset = FMath::Lerp(StartPositionSocketOffSet, FVector{0.f, -FCameraSholderOffset, 0.f}, FValue);
}

void UCharacterCameraBoom::InterpolateArmLengthProgress(float FValue)
{
    TargetArmLength = FMath::Lerp(FStartPositionSocketArmLength, FEndPositionSocketArmLength, FValue);
}

void UCharacterCameraBoom::InvertCameraSholder()
{
    FCameraSholderOffset = -FCameraSholderOffset;
}
