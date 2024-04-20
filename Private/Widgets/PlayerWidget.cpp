// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerWidget.h"
#include "ActorComponents/HealthComponent.h"
#include "ActorComponents/WeaponComponent.h"
#include "FrameworkClasses/AlphaStrikeGameState.h"
#include "FrameworkClasses/DeathmatchGameMode.h"
#include "Characters/BaseCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UPlayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AAlphaStrikeGameState* GameState{ Cast<AAlphaStrikeGameState>(GetWorld()->GetGameState()) };
	auto Controller{ GetOwningPlayer() };
	auto Pawn{ Controller->GetPawn() };
	auto Player{ Cast<ABaseCharacter>(Pawn) };
	UWorld* World{ GetWorld() };
	if (!GameState || !Player || !World)
	{
		return;
	}

	GameState->OnMatchTimeChange.AddUObject(this, &UPlayerWidget::SetMatchTime);

	Player->HealthComponent->OnHealthChanged.BindUObject(this, &UPlayerWidget::SetHealth);
	Player->WeaponComponent->OnAmmoInClipChanged.BindUObject(this, &UPlayerWidget::SetAmmoInClip);
	Player->WeaponComponent->OnTotalAmmoChanged.BindUObject(this, &UPlayerWidget::SetTotalAmmo);

	// If this is deathmatch, add team scoreboard
	ADeathmatchGameMode* DeathmatchGameMode{ Cast<ADeathmatchGameMode>(World->GetAuthGameMode()) };
	if (DeathmatchGameMode)
	{
		TeamsScoreboard->SetVisibility(ESlateVisibility::Visible);
		GameState->OnTeam1ScoreChange.AddUObject(this, &UPlayerWidget::SetTeam1Score);
		GameState->OnTeam2ScoreChange.AddUObject(this, &UPlayerWidget::SetTeam2Score);
	}
}

inline void UPlayerWidget::SetHealth(float CurrentHealth, float MaxHealth)
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}

inline void UPlayerWidget::SetAmmoInClip(uint16 Ammo)
{
	AmmoInClip->SetText(FText::AsNumber(Ammo));
}

inline void UPlayerWidget::SetTotalAmmo(uint16 Ammo)
{
	AmmoInClip->SetText(FText::AsNumber(Ammo));
}

inline void UPlayerWidget::SetMatchTime(uint16 NewTime)
{
	uint16 Minutes = NewTime / 60;
	uint16 Seconds = NewTime % 60;

	const FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	MatchTimer->SetText(FText::FromString(TimeString));
}

inline void UPlayerWidget::SetTeam1Score(uint16 NewScore)
{
	Team1Score->SetText(FText::AsNumber(NewScore));
}

inline void UPlayerWidget::SetTeam2Score(uint16 NewScore)
{
	Team2Score->SetText(FText::AsNumber(NewScore));
}