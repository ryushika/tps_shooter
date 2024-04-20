// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameworkClasses/BaseGameMode.h"
#include "FrameworkClasses/AlphaStrikePlayerState.h"
#include "Controllers/AlphaStrikePlayerController.h"
#include "Characters/BaseCharacter.h"
#include "Spawners/TeamActorSpawner.h"
#include <Kismet/GameplayStatics.h>

ABaseGameMode::ABaseGameMode() : Super()
{
	PlayerControllerClass = AAlphaStrikePlayerController::StaticClass();
	PlayerStateClass = AAlphaStrikePlayerState::StaticClass();
	DefaultPawnClass = ABaseCharacter::StaticClass();
}

void ABaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	World = GetWorld();

	SetPlayerStarts();
}

void ABaseGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	AAlphaStrikePlayerState* PlayerState{ NewPlayer->GetPlayerState<AAlphaStrikePlayerState>() };
	ETeam Team{ PlayerState->GetCurrentTeam() };
	AActor* PlayerStart{ PlayerStarts.FindRef(Team) };

	if (PlayerStart && !NewPlayer->IsPlayerController())
	{
		ATeamActorSpawner* ActorSpawner{ Cast<ATeamActorSpawner>(PlayerStart) };
		ABaseCharacter* Character{ ActorSpawner->CreateActor(World, AICharacterClass) };
		NewPlayer->Possess(Character);
	}
	else
	{
		RestartPlayerAtPlayerStart(NewPlayer, PlayerStart);
	}
}

void ABaseGameMode::OnPlayerDeath(AController* CharacterController, AController* KillerController)
{
	const FString CharacterName{ CharacterController->GetName() };
	const FString KillerName{ KillerController->GetName() };
	const FString KillMessage{ KillerName + " killed " + CharacterName };
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, KillMessage);

	Cast<ABaseCharacter>(CharacterController->GetCharacter())->
		HandleDeath(CharacterController, KillerController);
}

inline void ABaseGameMode::HandlePlayerRestart(AController* Controller)
{
	if (SpawnCooldownControllers.Contains(Controller))
	{
		return;
	}

	SpawnCooldownControllers.Add(Controller);
	FTimerHandle TimerHandle;

	GetWorldTimerManager().SetTimer(TimerHandle, [this, &Controller]()
		{
			RestartPlayer(Controller);
			SpawnCooldownControllers.Remove(Controller);
		},
		SpawnCooldown, false);
}

inline void ABaseGameMode::SetPlayerStarts()
{
	TArray<AActor*> PlayerStartsActors{};
	UGameplayStatics::GetAllActorsOfClass(World, ATeamActorSpawner::StaticClass(), PlayerStartsActors);
	for (AActor* Actor : PlayerStartsActors)
	{
		ATeamActorSpawner* PlayerStart{ Cast<ATeamActorSpawner>(Actor) };
		ETeam TeamTag{ PlayerStart->GetTeamTag() };
		PlayerStarts.Add(TeamTag, Actor);
	}
}