// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/WeaponComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::Fire()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (GetOwner())
	{
		// Get the skeletal mesh component (assuming your weapon is attached to a static mesh)
		UStaticMeshComponent* StaticMeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

		if (StaticMeshComponent)
		{
			// Get the socket transform
			SocketTransform = StaticMeshComponent->GetSocketTransform("BulletStart", RTS_World);
		}
	}

	if (PlayerController)
	{
		if (CanFire())
		{

			// Calculate end location based on max shoot distance
			FVector EndLocation = SocketTransform.GetLocation() + (SocketTransform.GetRotation().Vector() * MaxShootDistance);
			// Perform ray trace
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(GetOwner()); // Ignore the actor holding the weapon

			if (GetWorld()->LineTraceSingleByChannel(HitResult, SocketTransform.GetLocation(), EndLocation, ECC_Camera, CollisionParams))
			{
				// Handle hit object
				AActor* HitActor = HitResult.GetActor();

				if (HitActor)
				{
					UGameplayStatics::ApplyDamage(HitActor, DamageAmount, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
				}
			}

			LastFireTime = GetWorld()->GetTimeSeconds();

			// Optionally, draw a debug line for visualization
			if (bDrawDebugLine)
			{
				DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), EndLocation, FColor::Red, false, 2.0f, 0, 1.0f);
			}

			if (AmmoInClip > 0u)
			{
				OnAmmoInClipChanged.Execute(--AmmoInClip);
			}
			else if (TotalAmmo != 0u)
			{
				// TODO: Reload, maybe incapsulate in different method
			}
		}
	}
}

bool UWeaponComponent::CanFire()
{
	// Check if enough time has passed since the last shot
	return (GetWorld()->GetTimeSeconds() - LastFireTime) > FireRate;
}

void UWeaponComponent::InitWeapon(FWeaponStruct WeaponStruct)
{
	CurrentWeaponStruct = WeaponStruct;
}