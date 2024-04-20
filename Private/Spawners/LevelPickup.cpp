// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/LevelPickup.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ALevelPickup::ALevelPickup() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	RootComponent = CollisionComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelPickup::OnOverlap);
}

void ALevelPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpinActor(DeltaTime);
}

void ALevelPickup::BeginPlay()
{
	Super::BeginPlay();

	InitialZ = GetActorLocation().Z;
}

void ALevelPickup::HandleRespawn()
{
	SetActorHiddenInGame(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorldTimerManager().SetTimer(RespawnHandle, [this]()
		{
			SetActorHiddenInGame(false);
			CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		},
		RespawnTime, false);
}

void ALevelPickup::SpinActor(float DeltaTime)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);

	FVector NewLocation = GetActorLocation();
	NewLocation.Z = InitialZ + Amplitude * FMath::Sin(Frequency * RunningTime);
	SetActorLocation(NewLocation);

	RunningTime += DeltaTime;
}