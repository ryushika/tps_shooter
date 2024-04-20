// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/WeaponPickup.h"
#include "ActorComponents/WeaponComponent.h"

void AWeaponPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWeaponComponent* WeaponComponent = OtherActor->GetComponentByClass<UWeaponComponent>();

	if (WeaponComponent)
	{
		Super::HandleRespawn();
	}
}