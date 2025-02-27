// Fill out your copyright notice in the Description page of Project Settings.


#include "day_night_manager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"  // ✅ Add this to fix incomplete type error

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
	
}

// Called every frame
void Aday_night_manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Update Time of Day
    TimeOfDay += DeltaTime * TimeSpeed;
    if (TimeOfDay >= 24.0f)
    {
        TimeOfDay = 0.0f; // Reset at midnight
    }

    UpdateSunPosition();
}

void Aday_night_manager::UpdateSunPosition()
{
    if (SunLight)
    {
        // Calculate sun rotation based on time (0 to 24 hours -> 0 to 360 degrees)
        float SunPitch = (TimeOfDay / 24.0f) * 360.0f - 90.0f;
        SunLight->SetActorRotation(FRotator(SunPitch, 0.0f, 0.0f));
    }
}

