// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameworkClasses/AlphaStrikeHUD.h"
#include "FrameworkClasses/AlphaStrikeGameState.h"
#include "Widgets/PlayerWidget.h"
#include "Widgets/ScoreboardWidget.h"

AAlphaStrikeHUD::AAlphaStrikeHUD() : Super()
{
	PrimaryActorTick.bCanEverTick = false;
}

inline void AAlphaStrikeHUD::ShowScoreboardWidget()
{
	ScoreboardWidget->SetVisibility(ESlateVisibility::Visible);
}

inline void AAlphaStrikeHUD::HideScoreboardWidget()
{
	ScoreboardWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AAlphaStrikeHUD::BeginPlay()
{
	Super::BeginPlay();

	SetUpScoreboardWidget();
	SetUpPlayerWidget();
}

inline void AAlphaStrikeHUD::SetUpScoreboardWidget()
{
	AAlphaStrikeGameState* GameState{ GetWorld()->GetGameState<AAlphaStrikeGameState>() };
	ScoreboardWidget = GameState->GetScoreboardWidget();
	if (ScoreboardWidget)
	{
		ScoreboardWidget->AddToViewport();
		HideScoreboardWidget();
	}
}

inline void AAlphaStrikeHUD::SetUpPlayerWidget() const
{
	if (PlayerWidgetClass)
	{
		UPlayerWidget* PlayerWidget = CreateWidget<UPlayerWidget>
			(GetOwningPlayerController(), PlayerWidgetClass);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
		}
	}
}