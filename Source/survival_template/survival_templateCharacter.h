// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "player_state.h"
#include "Logging/LogMacros.h"
#include "ai_zombie.h"
#include "survival_templateCharacter.generated.h"

//class Aai_zombie;
class Acp_weapon;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class Asurvival_templateCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Craft_Action;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Fire_Action;

public:
	Asurvival_templateCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for crefting input */
	void Craft(const FInputActionValue& Value);

	/** Called for fire input */
	void Fire(const FInputActionValue& Value);

	/** Called for fire input */
	//void Sprint(const FInputActionValue& Value);
	void HandleStamina();
	void StopSprinting();
	void StartSprinting();

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ManageHealth();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//player state/component component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	Uplayer_state* PlayerStateComponent;

	// Sprint Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalWalkSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRegenRate = 0.10f;

	// Timer for stamina management
	FTimerHandle StaminaTimer;

	//combat
	float AttackRange = 200.0f; // Define attack range

	// Attack Montage
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* AttackMontage;

	//// Currently Equipped Weapon
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	//Acp_weapon* EquippedWeapon;

	// ✅ Simple Boolean to Check Weapon Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHasWeapon = false;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PerformWeaponTrace();

	void PerformSphereTrace(UStaticMeshComponent* WeaponMesh);
	
	// Function to handle animation notify events
	UFUNCTION()
	void OnAttackNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);


	void StartCraftingProcess();

	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting part")
	void crafting_process();

	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting part")
	void ui_health();
	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting part")
	void ui_stamina();
	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting part")
	void ui_resource();
	//
	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting part")
	void ui_wood();
	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting part")
	void ui_rock();
};

