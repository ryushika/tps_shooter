// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameworkClasses/FFAGameMode.h"
#include "FrameworkClasses/AlphaStrikeGameInstance.h"
#include "FrameworkClasses/AlphaStrikeGameState.h"
#include "FrameworkClasses/AlphaStrikePlayerState.h"
#include "AIController.h"
#include "Controllers/AlphaStrikePlayerController.h"

void AFFAGameMode::OnPlayerDeath(AController* CharacterController, AController* KillerController)
{
	AAlphaStrikePlayerState* CharacterPlayerState{ CharacterController->GetPlayerState<AAlphaStrikePlayerState>() };
	AAlphaStrikePlayerState* KillerPlayerState{ KillerController->GetPlayerState<AAlphaStrikePlayerState>() };

	CharacterPlayerState->AddDeath(CharacterController);
	KillerPlayerState->AddFrag(KillerController);

	HandlePlayerRestart(CharacterController);

	Super::OnPlayerDeath(CharacterController, KillerController);
}

void AFFAGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnBots();
}

inline void AFFAGameMode::SpawnBots()
{
	for (uint8 i{}; i < MaxPlayerQuantity - 1; ++i)
	{
		AAIController* BotAIController{ World->SpawnActor<AAIController>(
			AIControllerClass, FVector::ZeroVector, FRotator::ZeroRotator) };

		RestartPlayer(BotAIController);
		++PlayerQuantity;
	}
}
