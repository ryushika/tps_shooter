// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Controllers\AlphaStrikeAIController.h"
#include "FrameworkClasses/AlphaStrikeGameState.h"

AAlphaStrikeAIController::AAlphaStrikeAIController() : Super()
{
	bWantsPlayerState = true;
}

void AAlphaStrikeAIController::BeginPlay()
{
	Super::BeginPlay();

	AAlphaStrikeGameState* GameState = GetWorld()->GetGameState<AAlphaStrikeGameState>();
	GameState->OnPlayerAdded.Execute(this);
}