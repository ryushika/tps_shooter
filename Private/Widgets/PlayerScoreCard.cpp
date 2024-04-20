// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerScoreCard.h"
#include "Components/TextBlock.h"
#include "FrameworkClasses/AlphaStrikePlayerState.h"

void UPlayerScoreCard::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AAlphaStrikePlayerState* PlayerState{ Cast<AAlphaStrikePlayerState>(GetOwningPlayerState()) };
	if (PlayerState)
	{
		PlayerName->SetText(FText::FromString(PlayerState->GetPlayerName()));
		PlayerKills->SetText(FText::AsNumber(PlayerState->GetFrags()));
		PlayerDeaths->SetText(FText::AsNumber(PlayerState->GetDeaths()));
	}
}

inline void UPlayerScoreCard::ChangeFragsInList(uint16 Frags) const
{
	PlayerKills->SetText(FText::AsNumber(Frags));
}

inline void UPlayerScoreCard::ChangeDeathsInList(uint16 Deaths) const
{
	PlayerDeaths->SetText(FText::AsNumber(Deaths));
}
