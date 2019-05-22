// Fill out your copyright notice in the Description page of Project Settings.

#include "Cookbook.h"
#include "Pickup.h"
#include "PickupSpawner.h"


// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");

}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle DummyHandle;
	GetWorldTimerManager().SetTimer(DummyHandle, this, &APickupSpawner::SpawnPickup, 3.f, true);

}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APickupSpawner::SpawnPickup()
{

	FTransform SpawnTransform = Scene->GetComponentTransform();
	FVector SpawnLocation = SpawnTransform.GetLocation();
	SpawnLocation.X += FMath::RandRange(-200.0f, 200.0f);
	SpawnTransform.SetLocation(SpawnLocation);

	GetWorld()->SpawnActor<APickup>(PickupToSpawn, SpawnTransform);

}

