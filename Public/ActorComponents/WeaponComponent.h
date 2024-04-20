// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "FrameworkClasses/AlphaStrikeTypes.h"
#include "WeaponComponent.generated.h"


DECLARE_DELEGATE_OneParam(FOnAmmoInClipChanged, uint16)
DECLARE_DELEGATE_OneParam(FOnTotalAmmoChanged, uint16)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShootSignature, float, ReloadTime);

/**
* Weapon component for characters
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class ALPHASTRIKE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime = 2.f;

	UPROPERTY(EditAnywhere)
	float FireRate = 0.2f;

	float LastFireTime;

	UPROPERTY(BlueprintAssignable)
	FOnShootSignature OnShoot;

	FOnAmmoInClipChanged OnAmmoInClipChanged;
	FOnTotalAmmoChanged OnTotalAmmoChanged;

protected:
	virtual void BeginPlay() override;

private:
	uint16 AmmoInClip{ 7u };
	uint16 TotalAmmo{ 14u };
	uint16 ClipCapacity{ 7u };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess))
	float MaxShootDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess))
	bool bDrawDebugLine = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess))
	float DamageAmount = 10.0f;

	FTransform SocketTransform;

	bool CanFire();
private:
	UPROPERTY()
	FWeaponStruct CurrentWeaponStruct;

	void InitWeapon(FWeaponStruct WeaponStruct);
};