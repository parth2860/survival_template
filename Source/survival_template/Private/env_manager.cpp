// Fill out your copyright notice in the Description page of Project Settings.


#include "env_manager.h"

// Sets default values
Aenv_manager::Aenv_manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //DayNightSpeed = 5.0f;  // Default time speed
    //CurrentTime = 22.0f;   // Start game at night (22:00 / 10 PM)
}

// Called when the game starts or when spawned
void Aenv_manager::BeginPlay()
{
    Super::BeginPlay();

    if (LightActor)
    {
        // Start at night (11 PM)
        CurrentTime = 23.0f;
        UE_LOG(LogTemp, Warning, TEXT("Game starts at Night: %.1f"), CurrentTime);
    }
}

void Aenv_manager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (LightActor)
    {
        float RotationAmount = DayNightSpeed * DeltaTime;
        RotateSun(RotationAmount);

        CurrentTime += (RotationAmount / 360.0f) * 24.0f;
        if (CurrentTime >= 24.0f)
        {
            CurrentTime = 0.0f; // Reset after a full cycle
        }

        PrintCurrentTimeEvent();
    }
}

void Aenv_manager::RotateSun(float RotationAmount)
{
    if (LightActor)
    {
        float SunAngle = (CurrentTime / 24.0f) * 360.0f;
        FRotator NewRotation = LightActor->GetActorRotation();
        NewRotation.Pitch = SunAngle;
        LightActor->SetActorRotation(NewRotation);
    }
}

void Aenv_manager::PrintCurrentTimeEvent()
{
    FString TimeEvent;

    if (CurrentTime >= 23.0f || CurrentTime < 11.0f)
    {
        TimeEvent = "Night 🌙";
        get_zombie();
    }
    else
    {
        TimeEvent = "Morning ☀️";
        get_resource();
    }

    UE_LOG(LogTemp, Warning, TEXT("Current Time: %.1f - %s"), CurrentTime, *TimeEvent);
}

float Aenv_manager::GetCurrentTime() const
{
    return CurrentTime; // Returns time (0-24 hours)
}

