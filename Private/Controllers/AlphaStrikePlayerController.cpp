// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AlphaStrikePlayerController.h"
#include "FrameworkClasses/AlphaStrikeGameState.h"

void AAlphaStrikePlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void AAlphaStrikePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	AAlphaStrikeGameState* GameState = GetWorld()->GetGameState<AAlphaStrikeGameState>();
	GameState->OnPlayerAdded.Execute(this);
}
