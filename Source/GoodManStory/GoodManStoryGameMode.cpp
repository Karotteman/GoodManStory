// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GoodManStoryGameMode.h"
#include "GoodManStoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGoodManStoryGameMode::AGoodManStoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Character/Player/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
