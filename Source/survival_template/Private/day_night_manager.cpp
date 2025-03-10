
#include "day_night_manager.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
//#include "Components/AtmosphericFogComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Engine/ExponentialHeightFog.h"
//#include "Engine/AtmosphericFog.h"
//#include "Engine/SkyAtmosphere.h"  // ✅ Fixed for UE5

Aday_night_manager::Aday_night_manager()
{
    PrimaryActorTick.bCanEverTick = true;
}

// BeginPlay
void Aday_night_manager::BeginPlay()
{
    Super::BeginPlay();

    if (LightActor)
    {
        // Start at night (11 PM)
        CurrentTime = 23.0f;
        UE_LOG(LogTemp, Warning, TEXT("Game starts at Night: %.1f"), CurrentTime);
        
    }
}

// Tick function
void Aday_night_manager::Tick(float DeltaTime)
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
float Aday_night_manager::GetCurrentTime() const
{
    return CurrentTime; // This is the missing definition
}

void Aday_night_manager::RotateSun(float DeltaTime)
{
    //if (!LightActor) return;
    if (LightActor)
    {
        // Increase rotation over time
        float RotationAmount = DayNightSpeed * DeltaTime;

        // Get current rotation as Quaternion
        FQuat CurrentRotation = LightActor->GetActorQuat();

        // Create a rotation Quaternion for the Pitch (Y-axis in Unreal)
        FQuat RotationDelta = FQuat(FRotator(RotationAmount, 0.0f, 0.0f));

        // Apply new rotation
        LightActor->SetActorRotation(RotationDelta * CurrentRotation);
    }
}

void Aday_night_manager::PrintCurrentTimeEvent()
{
    if (!LightActor) return;

    // Get the current Pitch rotation (Y-axis)
    float SunPitch = LightActor->GetActorRotation().Euler().X; // Extract Pitch from Quaternion

    FString NewTimePhase;

    // Handle the expected range properly
    if (SunPitch >= -90.0f && SunPitch < 0.0f)
    {
        NewTimePhase = "Day";  // Pitch -90 to 0 -> Daytime
    }
    else if (SunPitch >= 0.0f && SunPitch <= 90.0f)
    {
        NewTimePhase = "Night"; // Pitch 0 to 90 -> Nighttime
    }
    else
    {
        NewTimePhase = "Unknown"; // Handle unexpected cases
    }

    // Only update and log if the phase changed
    if (!NewTimePhase.IsEmpty() && NewTimePhase != LastTimePhase)
    {
        LastTimePhase = NewTimePhase;
        UE_LOG(LogTemp, Warning, TEXT("Time Phase Changed: %s"), *NewTimePhase);
    }
}




