// Fill out your copyright notice in the Description page of Project Settings.


#include "day_night_manager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"  // ✅ Add this to fix incomplete type error
#include "Kismet/GameplayStatics.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h" // Fix for USkyLightComponent
//#include "Engine/SkyAtmosphere.h"
#include "Engine/SkyLight.h"         // ✅ Sky Light Component


// Sets default values
Aday_night_manager::Aday_night_manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aday_night_manager::BeginPlay()
{
	Super::BeginPlay();
    // 🌞 Find Sun (Directional Light)
    TArray<AActor*> FoundLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundLights);
    if (FoundLights.Num() > 0)
    {
        SunLight = Cast<ADirectionalLight>(FoundLights[0]);
    }

    // 🌌 Find Sky Sphere (BP_SkySphere)
    TArray<AActor*> FoundSkySpheres;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundSkySpheres);
    for (AActor* SkyActor : FoundSkySpheres)
    {
        if (SkyActor->GetName().Contains("BP_SkySphere"))
        {
            SkySphere = SkyActor;
            break;
        }
    }

    // ☁️ Find Sky Light
    TArray<AActor*> FoundSkyLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyLight::StaticClass(), FoundSkyLights);
    if (FoundSkyLights.Num() > 0)
    {
        SkyLight = Cast<ASkyLight>(FoundSkyLights[0]);
    }
}

// Called every frame
void Aday_night_manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    TimeOfDay += DeltaTime * TimeSpeed;
    if (TimeOfDay >= 24.0f)
    {
        TimeOfDay = 0.0f;
    }

    UpdateSunPosition();
    UpdateSkySphere();
    AdjustLighting();
}

void Aday_night_manager::UpdateSunPosition()
{
    if (SunLight)
    {
        float SunPitch = (TimeOfDay / 24.0f) * 360.0f - 90.0f;
        SunLight->SetActorRotation(FRotator(SunPitch, 0.0f, 0.0f));

        float Intensity = (TimeOfDay >= 6.0f && TimeOfDay <= 18.0f) ? 10.0f : 0.2f; // 🔆 Adjusted night intensity
        SunLight->GetLightComponent()->SetIntensity(Intensity);
    }
}

void Aday_night_manager::UpdateSkySphere()
{
    if (SkySphere)
    {
        UFunction* RefreshFunction = SkySphere->FindFunction(TEXT("RefreshMaterial"));
        if (RefreshFunction)
        {
            SkySphere->ProcessEvent(RefreshFunction, nullptr);
        }
    }
}

void Aday_night_manager::AdjustLighting()
{
    if (SkyLight)
    {
        USkyLightComponent* SkyLightComponent = SkyLight->GetLightComponent();
        if (SkyLightComponent)
        {
            float SkyBrightness = (TimeOfDay >= 18.0f || TimeOfDay <= 6.0f) ? 0.3f : 3.0f; // 🌙 Night brightness boost
            SkyLightComponent->SetIntensity(SkyBrightness);

            // 🔥 THIS LINE FIXES THE BLACK NIGHT ISSUE!
            SkyLightComponent->RecaptureSky();
        }
    }
}