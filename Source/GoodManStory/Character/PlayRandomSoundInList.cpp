// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayRandomSoundInList.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Animation/AnimSequenceBase.h"

#if WITH_EDITOR
#include "Logging/MessageLog.h"
#include "Misc/UObjectToken.h"
#endif

/////////////////////////////////////////////////////
// UPlayRandomSoundInList

UPlayRandomSoundInList::UPlayRandomSoundInList()
	: Super()
{
	VolumeMultiplier = 1.f;
	PitchMultiplier = 1.f;

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA
}

void UPlayRandomSoundInList::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	if (!Sounds.Num())
		return;
	
	// Don't call super to avoid call back in to blueprints
	const int32 IndexSound = FMath::RandHelper(Sounds.Num());

	if (Sounds[IndexSound])
	{
		if (Sounds[IndexSound]->IsLooping())
		{
			UE_LOG(LogAudio, Warning, TEXT("PlaySound notify: Anim %s tried to spawn infinitely looping sound asset %s. Spawning suppressed."), *GetNameSafe(Animation), *GetNameSafe(Sounds[IndexSound]));
			return;
		}

		if (bFollow)
		{
			UGameplayStatics::SpawnSoundAttached(Sounds[IndexSound], MeshComp, AttachName, FVector(ForceInit), EAttachLocation::SnapToTarget, false, VolumeMultiplier, PitchMultiplier, 0.f, SoundAttenuation);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), Sounds[IndexSound], MeshComp->GetComponentLocation(), VolumeMultiplier, PitchMultiplier, 0.f, SoundAttenuation);
		}
	}
}

FString UPlayRandomSoundInList::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

#if WITH_EDITOR
void UPlayRandomSoundInList::ValidateAssociatedAssets()
{
	static const FName NAME_AssetCheck("AssetCheck");

	for (auto&& Sound : Sounds)
	{
		if ((Sound != nullptr) && (Sound->IsLooping()))
		{
			UObject* ContainingAsset = GetContainingAsset();

			FMessageLog AssetCheckLog(NAME_AssetCheck);

			const FText MessageLooping = FText::Format(
                NSLOCTEXT("AnimNotify", "Sound_ShouldNotLoop", "Sound {0} used in anim notify for asset {1} is set to looping, but the slot is a one-shot (it won't be played to avoid leaking an instance per notify)."),
                FText::AsCultureInvariant(Sound->GetPathName()),
                FText::AsCultureInvariant(ContainingAsset->GetPathName()));
			AssetCheckLog.Warning()
                ->AddToken(FUObjectToken::Create(ContainingAsset))
                ->AddToken(FTextToken::Create(MessageLooping));

			if (GIsEditor)
			{
				AssetCheckLog.Notify(MessageLooping, EMessageSeverity::Warning, /*bForce=*/ true);
			}
		}
	}
}
#endif
