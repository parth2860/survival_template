// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/SphereComponent.h"
//#include "Components/StaticMeshComponent.h"
#include "resource_item.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Wood UMETA(DisplayName = "Wood"),
	Rock UMETA(DisplayName = "Rock")
};


UCLASS()
class SURVIVAL_TEMPLATE_API Aresource_item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aresource_item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    // Resource Type (Wood or Stone)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    EResourceType ResourceType;

    // Mesh Component for the Resource
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;

    // Collision Sphere for detecting player overlap
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USphereComponent* CollisionSphere;

    // Overlap function
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

};
