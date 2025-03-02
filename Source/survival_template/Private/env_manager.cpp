// Fill out your copyright notice in the Description page of Project Settings.


#include "env_manager.h"

// Sets default values
Aenv_manager::Aenv_manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DayNightSpeed = 5.0f;  // Default time speed
    CurrentTime = 22.0f;   // Start game at night (22:00 / 10 PM)
}

// Called when the game starts or when spawned
void Aenv_manager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

void Aenv_manager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (LightActor)
    {
        float RotationAmount = DayNightSpeed * DeltaTime; // Adjust rotation per frame
        RotateSun(RotationAmount);

        // Update in-game time (0 - 24 hours mapped to 360-degree rotation)
        CurrentTime += (RotationAmount / 360.0f) * 24.0f;
        if (CurrentTime >= 24.0f)
        {
            CurrentTime = 0.0f; // Reset after full cycle
        }

        // Print the current time event
        PrintCurrentTimeEvent();
    }
}

void Aenv_manager::RotateSun(float RotationAmount)
{
    if (LightActor)
    {
        // Convert CurrentTime (0 - 24) to proper sun angle
        float SunAngle = (CurrentTime / 24.0f) * 360.0f;

        // Set rotation: pitch controls the sun movement from sunrise to sunset
        FRotator NewRotation = LightActor->GetActorRotation();
        NewRotation.Pitch = SunAngle;  // Adjust pitch instead of roll
        LightActor->SetActorRotation(NewRotation);
    }
}

void Aenv_manager::PrintCurrentTimeEvent()
{
    FString TimeEvent;

    if (CurrentTime >= 5.0f && CurrentTime < 12.0f)
    {
        TimeEvent = "Morning 🌅";
    }
    else if (CurrentTime >= 12.0f && CurrentTime < 17.0f)
    {
        TimeEvent = "Afternoon ☀️";
    }
    else if (CurrentTime >= 17.0f && CurrentTime < 20.0f)
    {
        TimeEvent = "Evening 🌆";
    }
    else
    {
        TimeEvent = "Night 🌙";
    }

    UE_LOG(LogTemp, Warning, TEXT("Current Time: %.1f - %s"), CurrentTime, *TimeEvent);
}

float Aenv_manager::GetCurrentTime() const
{
    return CurrentTime; // Returns time (0-24 hours)
}

