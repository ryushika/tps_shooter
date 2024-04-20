// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

class ABaseCharacter;
class AAIController;
class AAlphaStrikePlayerController;
enum class ETeam : uint8;

/**
 * Base game mode to extend
 */
UCLASS(Abstract)
class ALPHASTRIKE_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseGameMode();
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override final;

	void RestartPlayer(AController* NewPlayer) override final;
	virtual void OnPlayerDeath(AController* CharacterController, AController* KillerController);

protected:
	inline virtual void SpawnBots() PURE_VIRTUAL(&ABaseGameMode::SpawnBots, return;);

	UPROPERTY(EditDefaultsOnly, Category = "Players|Spawn")
	float SpawnCooldown{ 3.f };
	inline void HandlePlayerRestart(AController* Controller);

	UPROPERTY(EditDefaultsOnly, Category = "Players|Quantity")
	uint16 MaxPlayerQuantity{ 10u };

	UPROPERTY()
	TObjectPtr<UWorld> World{};

	uint16 PlayerQuantity{};
	UPROPERTY(EditDefaultsOnly, Category = "Players|Bots", meta = (AllowPrivateAccess))
	TSubclassOf<ABaseCharacter> AICharacterClass;
	UPROPERTY(EditDefaultsOnly, Category = "Players|Bots", meta = (AllowPrivateAccess))
	TSubclassOf<AAIController> AIControllerClass;

private:
	inline void SetPlayerStarts();

	TMap<ETeam, AActor*> PlayerStarts{};
	TSet<const AController*> SpawnCooldownControllers{};
};