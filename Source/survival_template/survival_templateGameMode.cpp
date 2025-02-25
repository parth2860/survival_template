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
void Asurvival_templateGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnResources();
}
void Asurvival_templateGameMode::SpawnResources()
{
    for (int i = 0; i < 10; i++) // Spawn 10 resources
    {
        FVector SpawnLocation = FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), 50);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AActor* SpawnedResource = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation);
    }
}
