// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/TeamActorSpawner.h"
#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ATeamActorSpawner::ATeamActorSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetVisibility(true);
	BoxComponent->SetHiddenInGame(true);
	RootComponent = BoxComponent;
}

inline ABaseCharacter* ATeamActorSpawner::CreateActor(UWorld* World, TSubclassOf<ABaseCharacter> CharacterClass) const
{
	FVector Origin, BoxExtent;
	GetActorBounds(false, Origin, BoxExtent);

	double RandomX{ FMath::RandRange(-BoxExtent.X, BoxExtent.X) };
	double RandomY{ FMath::RandRange(-BoxExtent.Y, BoxExtent.Y) };
	FTransform Transform = GetActorTransform();
	Transform.SetLocation(FVector(RandomX, RandomY, Origin.Z));
	Transform.SetScale3D(FVector(FVector::OneVector));

	return World->SpawnActor<ABaseCharacter>(CharacterClass, Transform);
}

// Called when the game starts or when spawned
void ATeamActorSpawner::BeginPlay()
{
	Super::BeginPlay();
}