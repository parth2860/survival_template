// Fill out your copyright notice in the Description page of Project Settings.


#include "ai_zombie.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AIController.h"
#include "GameFramework/Controller.h"  // Use this instead of AIController.h
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
Aai_zombie::Aai_zombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aai_zombie::BeginPlay()
{
	Super::BeginPlay();
	
    // Start wandering behavior
    GetWorldTimerManager().SetTimer(RandomWalkTimerHandle, this, &Aai_zombie::StartRandomWalk, 3.0f, true);

}

// Called every frame
void Aai_zombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Check for player nearby
    AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (Player)
    {
        float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());

        if (Distance < DetectionRange)
        {
            ChasePlayer(Player);
        }
        else
        {
            // Resume random wandering if not chasing
            if (!GetWorldTimerManager().IsTimerActive(RandomWalkTimerHandle))
            {
                GetWorldTimerManager().SetTimer(RandomWalkTimerHandle, this, &Aai_zombie::StartRandomWalk, 3.0f, true);
            }
        }
    }
}

// Called to bind functionality to input
void Aai_zombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void Aai_zombie::StartRandomWalk()
{
    //
    //UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    //if (NavSystem)
    //{
    //    FVector RandomPoint;
    //    if (NavSystem->K2_GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), RandomPoint, WalkRadius))
    //    {
    //        GetCharacterMovement()->MaxWalkSpeed = 200.0f; // Normal speed for wandering
    //        MoveToLocation(RandomPoint);
    //    }
    //}
    //
    UWorld* World = GetWorld();
    if (!World) return;

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World);
    if (NavSystem)
    {
        FVector RandomPoint;
        if (NavSystem->K2_GetRandomReachablePointInRadius(World, GetActorLocation(), RandomPoint, WalkRadius))
        {
            MoveToLocation(RandomPoint);
        }
    }
}
void Aai_zombie::OnSeePlayer()
{
    AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (Player)
    {
        float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
        if (Distance < DetectionRange)
        {
            ChasePlayer(Player);
        }
    }
}

void Aai_zombie::ChasePlayer(AActor* Player)
{
    if (!Player) return;

    GetCharacterMovement()->MaxWalkSpeed = 400.0f; // Faster speed for chasing
    MoveToLocation(Player->GetActorLocation());

    float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
    if (Distance < AttackRange)
    {
        AttackPlayer();
    }
}

void Aai_zombie::AttackPlayer()
{
    AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (Player)
    {
        // Play attack animation
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance && AttackMontage)  // Ensure montage is valid
        {
            AnimInstance->Montage_Play(AttackMontage);
        }

        // Apply damage (optional: delay damage to sync with animation impact)
        UGameplayStatics::ApplyDamage(Player, AttackDamage, GetController(), this, nullptr);
    }
}
void Aai_zombie::MoveToLocation(const FVector& TargetLocation)
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        AIController->MoveToLocation(TargetLocation);
    }
}
//zombie attack-------------------------------------
float Aai_zombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    HitCount++;

    if (HitCount >= MaxHits)
    {
        Die();
    }

    return DamageAmount;

}

void Aai_zombie::Die()
{
    Destroy();
}




