// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "survival_template/survival_templateCharacter.h"
#include "player_state.generated.h"

//class survival_templateCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_TEMPLATE_API Uplayer_state : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Uplayer_state();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Player Health
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    float Health;

    // Player Stamina
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
    float Stamina;

    // Collected Wood & Stone
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Resources")
    int32 WoodCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Resources")
    int32 StoneCount;

    // Function to Collect Resource
    void CollectResource(FString ResourceType, int32 Amount);

    // Function to Craft Weapon
    bool CraftWeapon();

    FTimerHandle CraftingTimerHandle; // Timer to track crafting duration
    bool bIsCrafting = false; // Prevent crafting spam
    float CraftingTime = 30.0f; // Default crafting time (adjustable)

    UPROPERTY(EditDefaultsOnly, Category = "Crafting")
    TSubclassOf<AActor> WeaponClass; // Blueprint weapon class to spawn

    
};
