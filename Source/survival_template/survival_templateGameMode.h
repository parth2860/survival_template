// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "resource_item.h"
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
};



