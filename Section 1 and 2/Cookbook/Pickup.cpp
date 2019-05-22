// Fill out your copyright notice in the Description page of Project Settings.

#include "Cookbook.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = PickupMesh;

	PickupBox = CreateDefaultSubobject<UBoxComponent>("Box");
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	PickupMesh->SetWorldScale3D(FVector(FMath::RandRange(0.2f, 1.0f)));

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Destroy();
}

