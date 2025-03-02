// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
#include "env_manager.generated.h"

UCLASS()
class SURVIVAL_TEMPLATE_API Aenv_manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aenv_manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	ADirectionalLight* LightActor; // Reference to the Directional Light Actor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
	float DayNightSpeed = 5.0f; // Speed of time progression

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DayNight")
	float CurrentTime = 0.0f; // Tracks time in the day-night cycle

	UFUNCTION(BlueprintCallable, Category = "DayNight")
	void RotateSun(float RotationAmount);

	UFUNCTION(BlueprintCallable, Category = "DayNight")
	float GetCurrentTime() const; // Returns current time of day

	void PrintCurrentTimeEvent();//print  day event

};
