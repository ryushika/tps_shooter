// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UProgressBar;
class UImage;
class UTextBlock;
class UVerticalBox;

/**
 * Base player widget that is shown during gameplay
 */
UCLASS(Abstract)
class ALPHASTRIKE_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	inline void SetHealth(float CurrentHealth, float MaxHealth);
	inline void SetAmmoInClip(uint16 Ammo);
	inline void SetTotalAmmo(uint16 Ammo);
	inline void SetMatchTime(uint16 NewTime);
	inline void SetTeam1Score(uint16 NewScore);
	inline void SetTeam2Score(uint16 NewScore);

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> Crosshair;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ChosenWeapon;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> AmmoInClip;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalAmmo;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> MatchTimer;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UVerticalBox> TeamsScoreboard;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Team1Score;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Team2Score;
};
