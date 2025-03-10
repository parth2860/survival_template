﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "survival_templateCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// Asurvival_templateCharacter

Asurvival_templateCharacter::Asurvival_templateCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// In Constructor
	PlayerStateComponent = CreateDefaultSubobject<Uplayer_state>(TEXT("PlayerStateComponent"));

}

void Asurvival_templateCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//
	if (USkeletalMeshComponent* SkeletalMeshComp = GetMesh())
	{
		UAnimInstance* AnimInstance = SkeletalMeshComp->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &Asurvival_templateCharacter::OnAttackNotify);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void Asurvival_templateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Asurvival_templateCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Asurvival_templateCharacter::Look);

		// crafting
		EnhancedInputComponent->BindAction(Craft_Action, ETriggerEvent::Triggered, this, &Asurvival_templateCharacter::Craft);

		// fore
		EnhancedInputComponent->BindAction(Fire_Action, ETriggerEvent::Triggered, this, &Asurvival_templateCharacter::Fire);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void Asurvival_templateCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void Asurvival_templateCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void Asurvival_templateCharacter::Craft(const FInputActionValue& Value)
{
	if (PlayerStateComponent)
	{
		PlayerStateComponent->CraftWeapon();
	}
}
void Asurvival_templateCharacter::Fire(const FInputActionValue& Value)
{
	
	if (!bHasWeapon) // ✅ Check if Weapon is Equipped
	{
		UE_LOG(LogTemp, Warning, TEXT("No Weapon Equipped!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Attack Triggered"));

	if (bHasWeapon) 
	{
		// Play Attack Montage
		if (AttackMontage)
		{
			PlayAnimMontage(AttackMontage);
			// ✅ Perform Trace Based on Weapon Type
			PerformWeaponTrace();
		}
	}
	
}
// **Weapon Trace Function**
void Asurvival_templateCharacter::PerformWeaponTrace()
{
	if (USkeletalMeshComponent* SkeletalMeshComponent = GetMesh())
	{
		// Get all attached components (e.g., weapons)
		const TArray<USceneComponent*>& AttachedComponents = SkeletalMeshComponent->GetAttachChildren();

		for (USceneComponent* AttachedComponent : AttachedComponents)
		{
			// **Check if the attached component is a weapon**
			if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(AttachedComponent))
			{
				FString WeaponName = StaticMeshComponent->GetName();

				if (WeaponName == "WeaponMesh") // **Hammer (Sphere Trace)**
				{
					PerformSphereTrace(StaticMeshComponent);
				}
			}
		}
	}
}

// **Sphere Trace (For Hammer)**
void Asurvival_templateCharacter::PerformSphereTrace(UStaticMeshComponent* WeaponMesh)
{
	FVector StartTrace = WeaponMesh->GetSocketLocation(TEXT("impact_center"));
	float SphereRadius = 40.0f; // Adjust the size if needed
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignore the player
	TArray<FHitResult> HitResults;

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, StartTrace, StartTrace, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(SphereRadius), Params);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Sphere Trace Hit: %s"), *HitActor->GetName());

				// Check if the hit actor is a zombie (assuming your zombie class is AZombieCharacter)
				Aai_zombie* Zombie = Cast<Aai_zombie>(HitActor);
				if (Zombie)
				{
					// Apply damage to the zombie
					Zombie->TakeDamage(1.0f, FDamageEvent(), GetController(), this);

					// If zombie health reaches 0, destroy it
					/*if (Zombie->Health <= 0)
					{
						UE_LOG(LogTemp, Warning, TEXT("%s has died!"), *Zombie->GetName());
						Zombie->Destroy();
					}*/
				}
			}
		}
		//DrawDebugSphere(GetWorld(), StartTrace, SphereRadius, 12, FColor::Red, false, 2.0f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Sphere Trace Missed."));
		//DrawDebugSphere(GetWorld(), StartTrace, SphereRadius, 12, FColor::Green, false, 2.0f);
	}
}
void Asurvival_templateCharacter::OnAttackNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "AttackTrace") // Make sure this matches the Anim Notify name
	{
		PerformWeaponTrace();
	}
}
void Asurvival_templateCharacter::StartCraftingProcess()
{
	//if (bIsCrafting)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Already crafting!"));
	//	return;
	//}

	//UE_LOG(LogTemp, Warning, TEXT("Crafting in progress... Waiting %.1f seconds"), CraftingDuration);
	//bIsCrafting = true; // Block further crafting

	//// Start crafting timer
	//GetWorld()->GetTimerManager().SetTimer(CraftingTimerHandle, this, &Asurvival_templateCharacter::FinishCrafting, CraftingDuration, false);
	UE_LOG(LogTemp, Warning, TEXT(" crafting process!"));

    crafting_process();

}

