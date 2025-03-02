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
    if (bIsAttacking) return; // Prevent re-attacking while montage is playing

    AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (Player)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance && AttackMontage)
        {
            bIsAttacking = true; // Lock attack until montage completes
            AnimInstance->Montage_Play(AttackMontage);

            // Reset attack state after montage duration
            float MontageDuration = AttackMontage->GetPlayLength();
            GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetAttack, this, &Aai_zombie::ResetAttack, MontageDuration, false);
        }

        // Apply damage and count hits
        PlayerHitCount++; // Increase hit count
        UGameplayStatics::ApplyDamage(Player, AttackDamage, GetController(), this, nullptr);

        // Check if player should die
        if (PlayerHitCount >= MaxHitsBeforeDeath)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player has been hit 10 times! Player dies."));
            Player->Destroy(); // Destroy the player actor
        }
    }
}

// Reset function to allow another attack
void Aai_zombie::ResetAttack()
{
    bIsAttacking = false; // Allow attacking again
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
    //
    //Health -= DamageAmount;
    UE_LOG(LogTemp, Warning, TEXT("%s took damage! Health: %f"), *GetName());

    if (HitCount >= MaxHits)
    {
        Die();
    }

    return DamageAmount;
    

}
void Aai_zombie::Die()
{
    //
   /* bp_call();*/
    //
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

    if (!DeathMontage)  // Fix: Now correctly checking DeathMontage
    {
        UE_LOG(LogTemp, Error, TEXT("DeathMontage is NULL!"));
        Destroy();  // Destroy immediately if no animation
        return;
    }

    if (!AnimInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("AnimInstance is NULL!"));
        Destroy();  // Destroy immediately if animation fails
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Playing Death Animation!"));
    AnimInstance->Montage_Play(DeathMontage);

    // Destroy after death animation finishes
    float MontageDuration = DeathMontage->GetPlayLength();
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_Destroy, this, &Aai_zombie::DestroyZombie, MontageDuration, false);
}


void Aai_zombie::DestroyZombie()
{
    UE_LOG(LogTemp, Warning, TEXT("Destroying Zombie!"));
    Destroy();
}


