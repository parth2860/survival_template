// Fill out your copyright notice in the Description page of Project Settings.


#include "player_state.h"
#include "survival_template/survival_templateCharacter.h"

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
    //if (bIsCrafting)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Already crafting! Please wait."));
    //    return false;
    //}

    //if (WoodCount >= 5 && StoneCount >= 5)
    //{
    //    WoodCount -= 5;
    //    StoneCount -= 5;
    //    bIsCrafting = true; // Start crafting process

    //    UE_LOG(LogTemp, Warning, TEXT("Crafting started... (Time: %.1f seconds)"), CraftingTime);

    //    // Start crafting timer
    //   // GetWorld()->GetTimerManager().SetTimer(CraftingTimerHandle, this, &Uplayer_state::FinishCrafting, CraftingTime, false);
    //    //call player class fucntion
    //   

    //    return true; // Crafting started
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Not enough resources to craft a weapon!"));
    //    return false; // Not enough resources
    //}
    //
    if (bIsCrafting)
    {
        UE_LOG(LogTemp, Warning, TEXT("Already crafting! Please wait."));
        return false;
    }

    if (WoodCount >= 5 && StoneCount >= 5)
    {
        WoodCount -= 5;
        StoneCount -= 5;
        bIsCrafting = true; // Start crafting process

       // UE_LOG(LogTemp, Warning, TEXT("Crafting started... (Time: %.1f seconds)"), CraftingTime);

        // Get the Player Character
        Asurvival_templateCharacter* Player = Cast<Asurvival_templateCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

        if (Player)
        {
            Player->StartCraftingProcess();
            //UE_LOG(LogTemp, Warning, TEXT("calling player class for process!"));
        }

        return true; // Crafting started
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough resources to craft a weapon!"));
        return false; // Not enough resources
    }
}



