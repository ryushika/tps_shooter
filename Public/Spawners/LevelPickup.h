// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPickup.generated.h"

UCLASS(Abstract)
class ALPHASTRIKE_API ALevelPickup : public AActor
{
	GENERATED_BODY()

public:
	ALevelPickup();
	virtual void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Parameters", BlueprintReadWrite)
	float RespawnTime{ 20.f };
	void HandleRespawn();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) PURE_VIRTUAL(LevelPickup::OnOverlap, return;);
private:
	void SpinActor(float DeltaTime);
	UPROPERTY(EditAnywhere, Category = "Parameters", BlueprintReadWrite, meta = (AllowPrivateAccess))
	float RotationSpeed{ 50.0f };
	UPROPERTY(EditAnywhere, Category = "Parameters", BlueprintReadWrite, meta = (AllowPrivateAccess))
	float Amplitude{ 50.0f };
	UPROPERTY(EditAnywhere, Category = "Parameters", BlueprintReadWrite, meta = (AllowPrivateAccess))
	float Frequency{ 1.0f };
	UPROPERTY(EditAnywhere, Category = "Parameters", BlueprintReadWrite, meta = (AllowPrivateAccess))
	float RunningTime{ 0.0f };
	float InitialZ{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UBoxComponent> CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<class UStaticMeshComponent> Mesh;

	FTimerHandle RespawnHandle;
};