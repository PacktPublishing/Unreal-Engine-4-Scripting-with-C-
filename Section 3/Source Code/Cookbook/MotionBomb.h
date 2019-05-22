// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MotionBomb.generated.h"

UENUM()
enum class EMotionBombType : uint8
{
	MBT_InstantBoom UMETA(DisplayName = "Instant Boom"),
	MBT_DelayedBoom UMETA(DisplayName = "Timed Boom"),
	MBT_RandomTimedBoom UMETA(DisplayName = "Random Timed Boom")
};

USTRUCT()
struct FBombOptions
{

	GENERATED_BODY()

	FBombOptions()
	{
		BombDelayTime = 1.f;
		BombTriggeredColor = FColor::Red;
		ExplosionSize = 2.f;
		BombType = EMotionBombType::MBT_DelayedBoom;
	}

	UPROPERTY(EditAnywhere)
	EMotionBombType BombType;

	UPROPERTY(EditAnywhere)
	FColor BombTriggeredColor;

	UPROPERTY(EditAnywhere)
	float BombDelayTime;

	UPROPERTY(EditAnywhere)
	float ExplosionSize;

};

UCLASS()
class COOKBOOK_API AMotionBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMotionBomb();

	UPROPERTY(EditAnywhere)
	FBombOptions BombOptions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* BombInstance;

	UParticleSystem* ExplosionParticles;

	bool bBombIsTriggered;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* BombExplosionRadius;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* PulseParticles;
	
	void Explode();

	UFUNCTION()
	void OnBombTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
