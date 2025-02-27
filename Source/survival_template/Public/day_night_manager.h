// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "day_night_manager.generated.h"

UCLASS()
class SURVIVAL_TEMPLATE_API Aday_night_manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aday_night_manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The Sun Light (Directional Light)
	UPROPERTY(EditAnywhere, Category = "DayNight")
	class ADirectionalLight* SunLight;

	// Time Speed (How fast day/night cycle progresses)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	float TimeSpeed = 1.0f;//0.4f;  // 1 min full day cycle

	// Current time of day (0 to 24)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	float TimeOfDay = 12.0f;//6.0f

private:
	void UpdateSunPosition();

};
