// Copyright Epic Games, Inc. All Rights Reserved.

#include "survival_templateGameMode.h"
#include "survival_templateCharacter.h"
#include "UObject/ConstructorHelpers.h"

Asurvival_templateGameMode::Asurvival_templateGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
