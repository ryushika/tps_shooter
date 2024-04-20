// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameworkClasses/DeathmatchGameMode.h"
#include "FrameworkClasses/AlphaStrikeGameInstance.h"
#include "FrameworkClasses/AlphaStrikeGameState.h"
#include "FrameworkClasses/AlphaStrikePlayerState.h"
#include "AIController.h"
#include "Controllers/AlphaStrikePlayerController.h"

void ADeathmatchGameMode::OnPlayerDeath(AController* CharacterController, AController* KillerController)
{
	AAlphaStrikePlayerState* CharacterPlayerState{ CharacterController->GetPlayerState<AAlphaStrikePlayerState>() };
	AAlphaStrikePlayerState* KillerPlayerState{ KillerController->GetPlayerState<AAlphaStrikePlayerState>() };

	CastChecked<AAlphaStrikeGameState>(GameState)->AddTeamScore(KillerPlayerState->GetCurrentTeam());
	CharacterPlayerState->AddDeath(CharacterController);
	KillerPlayerState->AddFrag(KillerController);

	HandlePlayerRestart(CharacterController);

	Super::OnPlayerDeath(CharacterController, KillerController);
}

void ADeathmatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnBots();
}

inline void ADeathmatchGameMode::SpawnBots()
{
	for (uint8 i{}; i < MaxPlayerQuantity - 1; ++i)
	{
		AAIController* BotAIController{ World->SpawnActor<AAIController>(
			AIControllerClass, FVector::ZeroVector, FRotator::ZeroRotator) };

		if (PlayerQuantity < MaxPlayerQuantity)
		{
			BotAIController->GetPlayerState<AAlphaStrikePlayerState>()->SetCurrentTeam(ETeam::Blue);
		}
		else
		{
			BotAIController->GetPlayerState<AAlphaStrikePlayerState>()->SetCurrentTeam(ETeam::Red);
		}
		RestartPlayer(BotAIController);
		++PlayerQuantity;
	}
}
