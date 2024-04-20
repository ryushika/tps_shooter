// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardWidget.generated.h"

class UVerticalBox;
class UListView;
class UPlayerScoreCard;

/**
 * Scoreboard widget to show players' statistics
 */
UCLASS(Abstract)
class ALPHASTRIKE_API UScoreboardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	inline void AddPlayerToList(AController* Controller);

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UVerticalBox> PlayerStats;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UListView> PlayerStatsList;

	UPROPERTY(EditDefaultsOnly, Category = "Score Card", meta = (AllowPrivateAccess))
	TSubclassOf<UPlayerScoreCard> ScoreCardClass;
};