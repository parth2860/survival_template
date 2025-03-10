
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
        SetNightEnvironment();
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

// Rotate the directional light (Sun/Moon)
void Aday_night_manager::RotateSun(float DeltaTime)
{
    if (LightActor)
    {
        float SunAngle = (CurrentTime / 24.0f) * 360.0f;

        // Get the current rotation
        FRotator CurrentRotation = LightActor->GetActorRotation();

        // Create target rotation for smooth transition
        FRotator TargetRotation = CurrentRotation;
        TargetRotation.Pitch = SunAngle;

        // Smoothly interpolate rotation using Lerp
        FRotator SmoothedRotation = FMath::Lerp(CurrentRotation, TargetRotation, 0.05f); // 0.05f controls smoothness

        // Apply the new rotation
        LightActor->SetActorRotation(SmoothedRotation);
    }
}


// Print and adjust environment based on time
void Aday_night_manager::PrintCurrentTimeEvent()
{
    FString TimeEvent;

    if (CurrentTime >= 18.0f || CurrentTime < 6.0f) // Nighttime (6 PM - 6 AM)
    {
        TimeEvent = "Night 🌙";
        SetNightEnvironment();
        GetZombie();
    }
    else if (CurrentTime >= 6.0f && CurrentTime < 18.0f) // Daytime (6 AM - 6 PM)
    {
        TimeEvent = "Morning ☀️";
        SetDayEnvironment();
        GetResource();
    }
    else // Evening Transition (6 PM - 7 PM)
    {
        TimeEvent = "Evening 🌅";
        SetEveningEnvironment();
    }

    UE_LOG(LogTemp, Warning, TEXT("Current Time: %.1f - %s"), CurrentTime, *TimeEvent);
}

// Get current in-game time
float Aday_night_manager::GetCurrentTime() const
{
    return CurrentTime;
}

// Set nighttime environment
void Aday_night_manager::SetNightEnvironment()
{
    if (LightActor)
    {
        UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(LightActor->GetLightComponent());
        if (LightComponent)
        {
            LightComponent->SetIntensity(1.0f); // Dim the light
            LightComponent->SetLightColor(FLinearColor(1.0f, 1.0f, 1.0f)); // Dark blue
        }
    }
}

// Set daytime environment
void Aday_night_manager::SetDayEnvironment()
{
    if (LightActor)
    {
        UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(LightActor->GetLightComponent());
        if (LightComponent)
        {
            LightComponent->SetIntensity(5.0f); // Full brightness
            LightComponent->SetLightColor(FLinearColor(1.0f, 0.95f, 0.85f)); // Warm yellow
        }
    }
}

// Set evening environment
void Aday_night_manager::SetEveningEnvironment()
{
    if (LightActor)
    {
        UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(LightActor->GetLightComponent());
        if (LightComponent)
        {
            LightComponent->SetIntensity(2.5f); // Medium brightness
            LightComponent->SetLightColor(FLinearColor(1.0f, 0.5f, 0.3f)); // Orange-red
        }
    }
}