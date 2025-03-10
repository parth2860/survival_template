// Fill out your copyright notice in the Description page of Project Settings.


#include "resource_item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "player_state.h"
#include "GameFramework/Character.h"


//#include "survival_templateCharacter.h"

// Sets default values
Aresource_item::Aresource_item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create Mesh Component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Create Collision Sphere
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(RootComponent);
    CollisionSphere->SetSphereRadius(100.f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // Bind Overlap Event
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &Aresource_item::OnOverlap);

    // Randomly set the resource type when spawned
    int32 RandomValue = FMath::RandRange(0, 1);
    ResourceType = (RandomValue == 0) ? EResourceType::Wood : EResourceType::Rock;
   
}

// Called when the game starts or when spawned
void Aresource_item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aresource_item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aresource_item::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Player collected: %s"),
            *UEnum::GetValueAsString(ResourceType));

        //call here
        set_ui();

        // Destroy the resource after collection
        Destroy();
    }
    //
    {
        if (OtherActor)
        {
            ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
            if (PlayerCharacter)
            {
                Uplayer_state* PlayerState = PlayerCharacter->FindComponentByClass<Uplayer_state>();
                if (PlayerState)
                {
                    FString ResourceName = (ResourceType == EResourceType::Wood) ? "Wood" : "Stone";
                    PlayerState->CollectResource(ResourceName, 1);
                    Destroy();
                }
            }
        }
    }
}
