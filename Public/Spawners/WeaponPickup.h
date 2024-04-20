// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawners/LevelPickup.h"
#include "WeaponPickup.generated.h"

UCLASS(Abstract)
class ALPHASTRIKE_API AWeaponPickup : public ALevelPickup
{
	GENERATED_BODY()

protected:
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
