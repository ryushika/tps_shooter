// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamActorSpawner.generated.h"

class ABaseCharacter;
class UBoxComponent;
enum class ETeam : uint8;

/**
* Actor class that spawns actors based on team
*/
UCLASS()
class ALPHASTRIKE_API ATeamActorSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATeamActorSpawner();

	inline ABaseCharacter* CreateActor(UWorld* World, TSubclassOf<ABaseCharacter> CharacterClass) const;

	ETeam GetTeamTag() const
	{
		return TeamTag;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Used for intents
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,
		Category = "Team", meta = (AllowPrivateAccess))
	ETeam TeamTag{};
};