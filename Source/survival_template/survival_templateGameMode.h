// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "resource_item.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h" // For iterating actors in the world
#include "survival_templateGameMode.generated.h"

UCLASS(minimalapi)
class Asurvival_templateGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	Asurvival_templateGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnResources();
	void OnDayStart();
	void OnNightStart();

	// In Asurvival_templateGameMode.h
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ResourceClass1;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ResourceClass2;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ZombieClass;    // Zombie BP
};



