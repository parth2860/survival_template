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
    UE_LOG(LogTemp, Warning, TEXT("Game mode begin play - Spawning resources"));

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSystem) return;

    for (int i = 0; i < 50; i++) // Spawn 10 resources
    {
        FVector SpawnLocation;
        FNavLocation RandomNavLocation;

        // Ensure valid location within NavMesh
        if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 1000.0f, RandomNavLocation))
        {
            SpawnLocation = RandomNavLocation.Location;

            // Randomly select between ResourceClass1 and ResourceClass2
            TSubclassOf<AActor> ResourceToSpawn = (FMath::RandBool()) ? ResourceClass1 : ResourceClass2;

            GetWorld()->SpawnActor<AActor>(ResourceToSpawn, SpawnLocation, FRotator::ZeroRotator);

            UE_LOG(LogTemp, Warning, TEXT("Resource spawned at: %s"), *SpawnLocation.ToString());
        }
    }
}
void Asurvival_templateGameMode::OnDayStart()
{
    UE_LOG(LogTemp, Warning, TEXT("Day Started - Spawning Resources"));

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSystem) return;

    // Destroy any zombies remaining from the night
    for (TActorIterator<AActor> ZombieItr(GetWorld(), ZombieClass); ZombieItr; ++ZombieItr)
    {
        (*ZombieItr)->Destroy();
    }

    // Spawn resources
    for (int i = 0; i < 20; i++)
    {
        FNavLocation RandomNavLocation;
        if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 1000.0f, RandomNavLocation))
        {
            FVector SpawnLocation = RandomNavLocation.Location;

            // Randomly select between ResourceClass1 (Wood) and ResourceClass2 (Rock)
            TSubclassOf<AActor> ResourceToSpawn = (FMath::RandBool()) ? ResourceClass1 : ResourceClass2;
            GetWorld()->SpawnActor<AActor>(ResourceToSpawn, SpawnLocation, FRotator::ZeroRotator);
        }
    }
}

void Asurvival_templateGameMode::OnNightStart()
{
    UE_LOG(LogTemp, Warning, TEXT("Night Started - Spawning Zombies"));

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSystem) return;

    // Destroy any resources remaining from the day
    for (TActorIterator<AActor> ResourceItr(GetWorld(), ResourceClass1); ResourceItr; ++ResourceItr)
    {
        (*ResourceItr)->Destroy();
    }
    for (TActorIterator<AActor> ResourceItr(GetWorld(), ResourceClass2); ResourceItr; ++ResourceItr)
    {
        (*ResourceItr)->Destroy();
    }

    // Find Player Location
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController) return;

    APawn* PlayerPawn = PlayerController->GetPawn();
    if (!PlayerPawn) return;

    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    const float SafeDistance = 1000.0f; // Minimum distance from player
    const int MaxAttempts = 20;        // Prevent infinite loop in case no valid points are found

    // Spawn zombies
    for (int i = 0; i < 3; i++)
    {
        int Attempts = 0;

        while (Attempts < MaxAttempts)
        {
            FNavLocation RandomNavLocation;
            if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 1000.0f, RandomNavLocation))
            {
                FVector SpawnLocation = RandomNavLocation.Location;

                // Ensure zombie spawns a safe distance away from the player
                if (FVector::Dist(SpawnLocation, PlayerLocation) > SafeDistance)
                {
                    GetWorld()->SpawnActor<AActor>(ZombieClass, SpawnLocation, FRotator::ZeroRotator);
                    break; // Successfully spawned, move to next zombie
                }
            }

            Attempts++; // Prevent infinite attempts
        }

        if (Attempts >= MaxAttempts)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find valid zombie spawn location after %d attempts."), MaxAttempts);
        }
    }
}

