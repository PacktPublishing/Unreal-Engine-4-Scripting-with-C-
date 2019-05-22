// Fill out your copyright notice in the Description page of Project Settings.

#include "Cookbook.h"
#include "MotionBomb.h"


// Sets default values
AMotionBomb::AMotionBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	BombMesh->SetSimulatePhysics(true);
	BombMesh->SetEnableGravity(true);
	SetRootComponent(BombMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));

	if (CubeMesh.Object)
	{
		BombMesh->SetStaticMesh(CubeMesh.Object);
	}

	BombExplosionRadius = CreateDefaultSubobject<USphereComponent>(FName("BombExplosionRadius"));
	BombExplosionRadius->SetSphereRadius(300.f);
	BombExplosionRadius->SetupAttachment(BombMesh);
	BombExplosionRadius->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	BombExplosionRadius->OnComponentBeginOverlap.AddDynamic(this, &AMotionBomb::OnBombTriggered);

	bBombIsTriggered = false;

	PulseParticles = CreateDefaultSubobject<UParticleSystemComponent>(FName("PulseParticles"));
	PulseParticles->SetupAttachment(BombMesh);
	PulseParticles->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticlesAsset(TEXT("/Game/StarterContent/Particles/P_Explosion"));

	if (ExplosionParticlesAsset.Object)
	{
		ExplosionParticles = ExplosionParticlesAsset.Object;
	}


}

// Called when the game starts or when spawned
void AMotionBomb::BeginPlay()
{
	Super::BeginPlay();
	
	BombInstance = BombMesh->CreateDynamicMaterialInstance(0);

	if (BombOptions.BombType == EMotionBombType::MBT_InstantBoom)
	{
		BombOptions.BombDelayTime = 0.1f;
	}
	else if (BombOptions.BombType == EMotionBombType::MBT_RandomTimedBoom)
	{
		BombOptions.BombDelayTime = FMath::FRandRange(0.f, 2.f);
	}

}

// Called every frame
void AMotionBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bBombIsTriggered && BombInstance)
	{
		FLinearColor CurrentBombColor;
		BombInstance->GetVectorParameterValue(FName("BombColor"), CurrentBombColor);

		BombInstance->SetVectorParameterValue(FName("BombColor"), FMath::CInterpTo(CurrentBombColor, BombOptions.BombTriggeredColor, DeltaTime, 3.f));
	}

}

void AMotionBomb::OnBombTriggered(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor != UGameplayStatics::GetPlayerCharacter(this, 0))
		return;

	bBombIsTriggered = true;

	FTimerHandle DummyHandle;
	GetWorldTimerManager().SetTimer(DummyHandle, this, &AMotionBomb::Explode, BombOptions.BombDelayTime, false);


}

void AMotionBomb::Explode()
{

	BombMesh->SetVisibility(false);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, FTransform(GetActorLocation()))->SetWorldScale3D(FVector(BombOptions.ExplosionSize));

	FTimerDelegate DestroyBombDelegate;
	DestroyBombDelegate.BindLambda([&] {
		Destroy();
	});

	FTimerHandle DummyHandle;
	GetWorldTimerManager().SetTimer(DummyHandle, DestroyBombDelegate, 0.5f, false);

}