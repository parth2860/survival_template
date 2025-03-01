// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
//#include "Components/UStaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "survival_template/survival_templateCharacter.h" // Include the player class
#include "cp_weapon.generated.h"

class UStaticMeshComponent;
//class USphereComponent;
//class Asurvival_templateCharacter;

UCLASS()
class SURVIVAL_TEMPLATE_API Acp_weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acp_weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    //---------------------------
   // Weapon Mesh
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* WeaponMesh;

    // Collision Sphere for Pickup
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* PickupSphere;

    // Function called when player overlaps
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

    // Function to attach weapon to player
    void AttachToPlayer(Asurvival_templateCharacter* Player);
};
