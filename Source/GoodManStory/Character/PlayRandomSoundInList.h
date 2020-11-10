// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Sound/SoundAttenuation.h"

#include "PlayRandomSoundInList.generated.h"

class UAnimSequenceBase;
class USkeletalMeshComponent;
class USoundBase;
class USoundAttenuation;

UCLASS(const, hidecategories=Object, collapsecategories, meta=(DisplayName="Play random sound in list"))
class GOODMANSTORY_API UPlayRandomSoundInList : public UAnimNotify
{
	GENERATED_BODY()

	public:

	UPlayRandomSoundInList();

	// Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
#if WITH_EDITOR
	virtual void ValidateAssociatedAssets() override;
#endif
	// End UAnimNotify interface

	// Sound to Play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	TArray<USoundBase*> Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	USoundAttenuation* SoundAttenuation = nullptr;

	// Volume Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	float VolumeMultiplier;

	// Pitch Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	float PitchMultiplier;

	// If this sound should follow its owner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	uint32 bFollow:1;

	// Socket or bone name to attach sound to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(EditCondition="bFollow", ExposeOnSpawn = true))
	FName AttachName;
};


