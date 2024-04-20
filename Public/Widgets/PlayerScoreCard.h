// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PlayerScoreCard.generated.h"

class UTextBlock;

/**
 * Widget card to show in scoreboard
 */
UCLASS(Abstract)
class ALPHASTRIKE_API UPlayerScoreCard : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	inline void ChangeFragsInList(uint16 Frags) const;
	inline void ChangeDeathsInList(uint16 Deaths) const;

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerName;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerKills;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerDeaths;
};