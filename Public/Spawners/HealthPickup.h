// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawners/LevelPickup.h"
#include "HealthPickup.generated.h"

/**
 *
 */
UCLASS()
class ALPHASTRIKE_API AHealthPickup : public ALevelPickup
{
	GENERATED_BODY()

protected:
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere, Category = "Parameters", BlueprintReadWrite, meta = (AllowPrivateAccess))
	float HealAmount{ 50.f };
};