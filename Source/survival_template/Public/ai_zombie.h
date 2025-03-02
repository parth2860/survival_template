// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"
#include "ai_zombie.generated.h"

UCLASS()
class SURVIVAL_TEMPLATE_API Aai_zombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Aai_zombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//zombie walk
	void StartRandomWalk(); // Picks a random location to walk
	void ChasePlayer(AActor* Player); // Starts chasing the player
	void AttackPlayer(); // Attacks when in range
	void OnSeePlayer(); // Called when the player is spotted
	void MoveToLocation(const FVector& TargetLocation); // Corrected function


	UPROPERTY(EditAnywhere, Category = "Zombie AI")
	float DetectionRange = 800.0f; // Sight range

	UPROPERTY(EditAnywhere, Category = "Zombie AI")
	float AttackRange = 120.0f; // Attack range

	UPROPERTY(EditAnywhere, Category = "Zombie AI")
	float WalkRadius = 600.0f; // Random movement range

	UPROPERTY(EditAnywhere, Category = "Zombie AI")
	float AttackDamage = 20.0f; // Damage per attack

	FTimerHandle RandomWalkTimerHandle;

	//zombie attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage;

	int HitCount = 2;
	int MaxHits = 15; // Zombie dies after 2 hits

	void Die();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,class AController* EventInstigator, AActor* DamageCauser) override;

	// Attack Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* DeathMontage;

	void DestroyZombie();

	FTimerHandle TimerHandle_Destroy;

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void bp_call();


};
