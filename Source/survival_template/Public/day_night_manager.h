// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
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

    // Day/Night cycle logic
    UFUNCTION(BlueprintCallable, Category = "DayNight")
    void RotateSun(float RotationAmount);

    UFUNCTION(BlueprintCallable, Category = "DayNight")
    float GetCurrentTime() const;

    void PrintCurrentTimeEvent();

    //// Environmental settings
    //void SetNightEnvironment();
    //void SetDayEnvironment();
    //void SetMorningEnvironment();
    //void SetAfternoonEnvironment();
    //void SetEveningEnvironment();

    // Blueprint event functions
    UFUNCTION(BlueprintImplementableEvent, Category = "SpawnEvent")
    void GetZombie();

    UFUNCTION(BlueprintImplementableEvent, Category = "SpawnEvent")
    void GetResource();

private:
    // Directional Light Reference
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight", meta = (AllowPrivateAccess = "true"))
    ADirectionalLight* LightActor;

    // Speed of the day-night cycle
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight", meta = (AllowPrivateAccess = "true"))
    float DayNightSpeed = 5.0f;

    // Current in-game time
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight", meta = (AllowPrivateAccess = "true"))
    float CurrentTime = 6.0f;

    UPROPERTY(VisibleAnywhere, Category = "DayNight")
    FString LastTimePhase;


};
