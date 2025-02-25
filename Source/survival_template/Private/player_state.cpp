// Fill out your copyright notice in the Description page of Project Settings.


#include "player_state.h"

// Sets default values for this component's properties
Uplayer_state::Uplayer_state()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Uplayer_state::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Uplayer_state::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

