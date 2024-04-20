// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE_TwoParams(FOnDeath, AController*, AController*)
DECLARE_DELEGATE_TwoParams(FOnHealthChanged, float, float)

/**
* Health component for characters
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ALPHASTRIKE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	float GetHealth() const
	{
		return Health;
	}

	float GetMaxHealth() const
	{
		return MaxHealth;
	}

	void Heal(float HealAmount);

	bool IsDead() const
	{
		return Health <= 0.0f;
	}

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess))
	float MaxHealth{ 100.f };

	float Health;
};
