// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/HealthPickup.h"
#include "ActorComponents/HealthComponent.h"

void AHealthPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHealthComponent* HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>();

	if (HealthComponent)
	{
		if (HealthComponent->GetHealth() != HealthComponent->GetMaxHealth())
		{
			HealthComponent->Heal(HealAmount);
			Super::HandleRespawn();
		}
	}
}