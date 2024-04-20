// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AlphaStrikeTypes.generated.h"

USTRUCT(BlueprintType)
struct FWeaponStruct : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh *WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> ParticleTrail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> HitParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> MuzzleFlashParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class USoundBase>> ShootingSounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 30.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;
};
