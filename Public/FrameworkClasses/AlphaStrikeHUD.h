// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AlphaStrikeHUD.generated.h"

class UPlayerWidget;
class UScoreboardWidget;

/**
 * Default player HUD
 */
UCLASS()
class ALPHASTRIKE_API AAlphaStrikeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAlphaStrikeHUD();

	inline void ShowScoreboardWidget();
	inline void HideScoreboardWidget();

protected:
	void BeginPlay() override;

private:
	inline void SetUpScoreboardWidget();
	inline void SetUpPlayerWidget() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		Category = "Widget", meta = (AllowPrivateAccess))
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	// Pointing to Widget in GameState
	TObjectPtr<UScoreboardWidget> ScoreboardWidget;
};