// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_weapon.h"

// Sets default values
Acp_weapon::Acp_weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create Weapon Mesh
    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    SetRootComponent(WeaponMesh);

    // Create Pickup Sphere
    PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
    PickupSphere->SetupAttachment(WeaponMesh);
    PickupSphere->SetSphereRadius(100.0f);

    // Enable Overlap
    PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &Acp_weapon::OnOverlapBegin);

}

// Called when the game starts or when spawned
void Acp_weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Overlap Function
void Acp_weapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
    Asurvival_templateCharacter* Player = Cast<Asurvival_templateCharacter>(OtherActor);
    if (Player)
    {
        AttachToPlayer(Player);
    }
}
// Attach Weapon to Player (Directly handles attachment)
void Acp_weapon::AttachToPlayer(Asurvival_templateCharacter* Player)
{
    if (Player)
    {
        AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
        SetOwner(Player);
        PickupSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Disable pickup collision
    }
}