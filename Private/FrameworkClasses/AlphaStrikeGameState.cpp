// Fill out your copyright notice in the Description page of Project Settings.

#include "FrameworkClasses/AlphaStrikeGameState.h"
#include "FrameworkClasses/AlphaStrikeGameInstance.h"
#include "Controllers/AlphaStrikePlayerController.h"
#include "Widgets/ScoreboardWidget.h"

AAlphaStrikeGameState::AAlphaStrikeGameState() : Super()
{
	SetActorTickInterval(TIMER_REFRESH_COOLDOWN_SECONDS);
	bAllowTickBeforeBeginPlay = false;
	PrimaryActorTick.bCanEverTick = true;
}

void AAlphaStrikeGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetUpScoreboardWidget();
}

void AAlphaStrikeGameState::Tick(float DeltaSeconds)
{
	MatchTime -= GetActorTickInterval();
	OnMatchTimeChange.Broadcast(MatchTime);

	if (MatchTime <= 0u)
	{
		OnMatchEnd.Execute();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Game has ended!"));
	}
}

inline void AAlphaStrikeGameState::AddTeamScore(ETeam Team)
{
	switch (Team)
	{
	case ETeam::None:
		break;
	case ETeam::Blue:
		OnTeam1ScoreChange.Broadcast(++Team1Score);
		break;
	case ETeam::Red:
		OnTeam2ScoreChange.Broadcast(++Team2Score);
		break;
	default:
		break;
	}
}

void AAlphaStrikeGameState::BeginPlay()
{
	Super::BeginPlay();

	MatchTime = StartingMatchTimeSeconds;
}

inline void AAlphaStrikeGameState::SetUpScoreboardWidget()
{
	if (ScoreboardWidgetClass)
	{
		ScoreboardWidget = CreateWidget<UScoreboardWidget>
			(GetWorld(), ScoreboardWidgetClass);
		OnPlayerAdded.BindUObject(ScoreboardWidget, &UScoreboardWidget::AddPlayerToList);
	}
}