// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "day_night_manager.generated.h"

UENUM(BlueprintType)
enum class EDayTime : uint8
{
	Morning     UMETA(DisplayName = "Morning"),
	Afternoon   UMETA(DisplayName = "Afternoon"),
	Evening     UMETA(DisplayName = "Evening"),
	Night       UMETA(DisplayName = "Night")
};

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

	UPROPERTY(EditAnywhere, Category = "DayNight")
	class ADirectionalLight* SunLight;  // Sun

	UPROPERTY(EditAnywhere, Category = "DayNight")
	AActor* SkySphere;  // SkySphere Actor

	UPROPERTY(EditAnywhere, Category = "DayNight")
	class ASkyLight* SkyLight;  // Ambient Light

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight", meta = (AllowPrivateAccess = "true"))
	float TimeOfDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight", meta = (AllowPrivateAccess = "true"))
	float TimeSpeed;

	void UpdateSunPosition();
	void UpdateSkySphere();
	void AdjustLighting();
};
