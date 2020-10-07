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
    
    TimeLine = FTimeline{};
    FOnTimelineFloat       progressFunction{};
    FOnTimelineEventStatic finishFunction{};

    progressFunction.BindUFunction(this, "SwitchCameraModeProgress");
    finishFunction.BindUFunction(this, "InvertCameraSholder");

    if (!Curve)
    {
        const ConstructorHelpers::FObjectFinder<UCurveFloat> DefaultCurve(
            TEXT("CurveFloat'/Game/Assets/Curve/BasicBlendCurve.BasicBlendCurve'"));
        
        if (DefaultCurve.Object)
        {
            TimeLine.AddInterpFloat(DefaultCurve.Object, progressFunction, FName{TEXT("BlendCamPos")});

        }
        else
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Cannot find curve"));
        }
    }
    else
    {
        TimeLine.AddInterpFloat(Curve, progressFunction, FName{TEXT("BlendCamPos")});
    }

    TimeLine.SetTimelineFinishedFunc(finishFunction);
    TimeLine.SetPlayRate(FPlayRateCameraTransition);
    TimeLine.SetTimelineLength(1.f);
}

void UCharacterCameraBoom::InterpolatePosition(FVector NewPosition)
{
    StartPosition   = SocketOffset;
    EndPosition     = NewPosition;

    if (TimeLine.IsPlaying())
    {
        InvertCameraSholder();
    }
    
    TimeLine.PlayFromStart();
    
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("SwitchCameraMode"));
}

void UCharacterCameraBoom::Update(float FDeltaTime)
{
    if (TimeLine.IsPlaying())
    {
        TimeLine.TickTimeline(FDeltaTime);
    }
}
    
void UCharacterCameraBoom::SwitchCameraModeProgress(float FValue)
{
    //TODO: Can be replace by end position
    SocketOffset = FMath::Lerp(StartPosition, FVector{0.f, -FCameraSholderOffset, 0.f}, FValue);
}
    
void UCharacterCameraBoom::InvertCameraSholder()
{
    FCameraSholderOffset = -FCameraSholderOffset;
}