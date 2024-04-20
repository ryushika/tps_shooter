// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AlphaStrikeGameState.generated.h"

DECLARE_DELEGATE(FOnMatchEnd)
DECLARE_DELEGATE_OneParam(FOnPlayerAdded, AController*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchTimeChange, uint16)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTeam1ScoreChange, uint16)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTeam2ScoreChange, uint16)

enum class ETeam : uint8;
class UScoreboardWidget;

/**
 * Base game state for game
 */
UCLASS()
class ALPHASTRIKE_API AAlphaStrikeGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AAlphaStrikeGameState();
	void PostInitializeComponents() override;
	void Tick(float DeltaSeconds) override;

	FOnMatchEnd OnMatchEnd;
	FOnPlayerAdded OnPlayerAdded;
	FOnMatchTimeChange OnMatchTimeChange;
	FOnTeam1ScoreChange OnTeam1ScoreChange;
	FOnTeam2ScoreChange OnTeam2ScoreChange;

	inline void AddTeamScore(ETeam Team);

	UScoreboardWidget* GetScoreboardWidget() const
	{
		return ScoreboardWidget;
	}

protected:
	void BeginPlay() override;

private:
	const uint8 TIMER_REFRESH_COOLDOWN_SECONDS{ 1u };

	UPROPERTY(EditDefaultsOnly, Category = "Match|Time", meta = (AllowPrivateAccess))
	uint16 StartingMatchTimeSeconds;
	uint16 MatchTime;

	uint16 Team1Score{};
	uint16 Team2Score{};


	UPROPERTY(EditDefaultsOnly, Category = "Match|Scoreboard", meta = (AllowPrivateAccess))
	TSubclassOf<UScoreboardWidget> ScoreboardWidgetClass;
	UPROPERTY()
	TObjectPtr<UScoreboardWidget> ScoreboardWidget;
	void SetUpScoreboardWidget();
};