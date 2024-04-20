// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "DeathmatchGameMode.generated.h"

/**
 * Game mode for team Deathmatch
 */
UCLASS(Abstract)
class ALPHASTRIKE_API ADeathmatchGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	virtual void OnPlayerDeath(AController* CharacterController, AController* KillerController) override;

protected:
	void BeginPlay() override;

	inline virtual void SpawnBots() override;
};