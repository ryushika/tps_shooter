// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AlphaStrikeAIController.generated.h"

/**
 * Base AI controller for bots
 */
UCLASS()
class ALPHASTRIKE_API AAlphaStrikeAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAlphaStrikeAIController();

protected:
	void BeginPlay() override;
};
