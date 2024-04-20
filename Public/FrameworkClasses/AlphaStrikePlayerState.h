// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AlphaStrikePlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFragsChanged, uint16)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeathsChanged, uint16)

enum class ETeam : uint8;

/**
 * Player state during gameplay
 */
UCLASS()
class ALPHASTRIKE_API AAlphaStrikePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetCurrentTeam(ETeam Team)
	{
		CurrentTeam = Team;
	}
	ETeam GetCurrentTeam() const
	{
		return CurrentTeam;
	}
	void SetFrags(uint16 NewFrags)
	{
		Frags = NewFrags;
	}
	void AddFrag(AController* Controller)
	{
		OnFragsChanged.Broadcast(++Frags);
	}
	uint16 GetFrags() const
	{
		return Frags;
	}
	void SetDeaths(uint16 NewDeaths)
	{
		Deaths = NewDeaths;
	}
	void AddDeath(AController* Controller)
	{
		OnDeathsChanged.Broadcast(++Deaths);
	}
	uint16 GetDeaths() const
	{
		return Deaths;
	}

	FOnFragsChanged OnFragsChanged;
	FOnDeathsChanged OnDeathsChanged;

private:
	ETeam CurrentTeam{};
	uint16 Frags{};
	uint16 Deaths{};
};