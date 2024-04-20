// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/HealthComponent.h"
#include "Characters/BaseCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::Heal(float HealthAmount)
{
	Health = FMath::Clamp(Health + HealthAmount, 0.f, MaxHealth);

	OnHealthChanged.ExecuteIfBound(Health, MaxHealth);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead())
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.ExecuteIfBound(Health, MaxHealth);

	if (IsDead())
	{
		ABaseCharacter* Character{ Cast<ABaseCharacter>(DamagedActor) };
		AController* CharacterController{ Character->GetController() };
		if (CharacterController)
		{
			OnDeath.Execute(CharacterController, InstigatedBy);
		}
	}
}