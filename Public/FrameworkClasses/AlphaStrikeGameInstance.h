// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AlphaStrikeGameInstance.generated.h"

/**
* Teams enum
*/
UENUM()
enum class ETeam : uint8
{
	None,
	Blue,
	Red
};

UCLASS()
class ALPHASTRIKE_API UAlphaStrikeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayLevel(const FString& GameMode);
};