// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ScoreboardWidget.h"
#include "Components/ListView.h"
#include "Widgets/PlayerScoreCard.h"
#include "FrameworkClasses/AlphaStrikePlayerState.h"

inline void UScoreboardWidget::AddPlayerToList(AController* Controller)
{
	UPlayerScoreCard* NewPlayerScoreCard{ NewObject<UPlayerScoreCard>(this, ScoreCardClass) };
	PlayerStatsList->AddItem(NewPlayerScoreCard);
	AAlphaStrikePlayerState* PlayerState{ Controller->GetPlayerState<AAlphaStrikePlayerState>() };
	if (PlayerState)
	{
		PlayerState->OnFragsChanged.AddUObject(NewPlayerScoreCard, &UPlayerScoreCard::ChangeFragsInList);
		PlayerState->OnDeathsChanged.AddUObject(NewPlayerScoreCard, &UPlayerScoreCard::ChangeDeathsInList);
	}
}