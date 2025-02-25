// Fill out your copyright notice in the Description page of Project Settings.


#include "player_state.h"

// Sets default values for this component's properties
Uplayer_state::Uplayer_state()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	// Initialize Default Values
	Health = 100.0f;
	Stamina = 100.0f;
	WoodCount = 0;
	StoneCount = 0;
}


// Called when the game starts
void Uplayer_state::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Uplayer_state::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
// Collect Resources (Wood or Stone)
void Uplayer_state::CollectResource(FString ResourceType, int32 Amount)
{
    if (ResourceType == "Wood")
    {
        WoodCount += Amount;
        UE_LOG(LogTemp, Warning, TEXT("Collected %d Wood. Total: %d"), Amount, WoodCount);
    }
    else if (ResourceType == "Stone")
    {
        StoneCount += Amount;
        UE_LOG(LogTemp, Warning, TEXT("Collected %d Stone. Total: %d"), Amount, StoneCount);
    }
}

// Craft a Weapon (Requires 5 Wood & 5 Stone)
bool Uplayer_state::CraftWeapon()
{
    if (WoodCount >= 5 && StoneCount >= 5)
    {
        WoodCount -= 5;
        StoneCount -= 5;
        UE_LOG(LogTemp, Warning, TEXT("Weapon Crafted! Remaining - Wood: %d, Stone: %d"), WoodCount, StoneCount);
        return true; // Successfully crafted
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough resources to craft a weapon!"));
        return false; // Not enough resources
    }
}

