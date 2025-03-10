
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
        // Start the game at night (11 PM)
        CurrentTime = 23.0f;
        UE_LOG(LogTemp, Warning, TEXT("Game starts at Night: %.1f"), CurrentTime);
    }
}

// Tick function (Runs every frame)
void Aday_night_manager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (LightActor)
    {
        RotateSun(DeltaTime);   // Rotate the sun
        UpdateCurrentTime();    // Update the game time
        PrintCurrentTimeEvent(); // Print day/night event if needed
    }
}

// Get current in-game time
float Aday_night_manager::GetCurrentTime() const
{
    return CurrentTime;
}

// Rotate the sun while keeping cycle smooth
void Aday_night_manager::RotateSun(float DeltaTime)
{
    if (!LightActor) return;

    float RotationAmount = DayNightSpeed * DeltaTime;

    // Get current rotation
    FRotator NewRotation = LightActor->GetActorRotation();
    NewRotation.Pitch += RotationAmount;

    // Keep rotation within valid range (-90 to 90)
    if (NewRotation.Pitch > 90.0f)
    {
        NewRotation.Pitch = -90.0f; // Reset cycle to maintain smooth loop
    }

    LightActor->SetActorRotation(NewRotation);
}

// Map sun position to a 24-hour clock
void Aday_night_manager::UpdateCurrentTime()
{
    if (!LightActor) return;

    float SunPitch = LightActor->GetActorRotation().Pitch; // Get Pitch

    // Map Pitch (-90 to 90) to (0 to 24 hours)
    CurrentTime = FMath::GetMappedRangeValueClamped(FVector2D(-90.0f, 90.0f), FVector2D(0.0f, 24.0f), SunPitch);
}

// Correctly detect Day/Night transitions
void Aday_night_manager::PrintCurrentTimeEvent()
{
    if (!LightActor) return;

    float SunPitch = LightActor->GetActorRotation().Pitch;

    FString NewTimePhase;

    // Day (SunPitch -90 to 0) | Night (SunPitch 0 to 90)
    if (SunPitch >= -90.0f && SunPitch < 0.0f)
    {
        NewTimePhase = "Day";
    }
    else if (SunPitch >= 0.0f && SunPitch <= 90.0f)
    {
        NewTimePhase = "Night";
    }

    // Only log when the phase actually changes
    if (NewTimePhase != LastTimePhase)
    {
        LastTimePhase = NewTimePhase;
        UE_LOG(LogTemp, Warning, TEXT("Time Phase Changed: %s"), *NewTimePhase);
    }
}






