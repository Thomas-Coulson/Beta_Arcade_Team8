// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player_Pawn.h"
#include "Beta_Arcade_Team8GameModeBase.generated.h"


UCLASS()
class BETA_ARCADE_TEAM8_API ABeta_Arcade_Team8GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	FTimerHandle m_levelTimerHandle;
	float m_currentTimeSecconds = 0;
	float m_timerInterval = 0.01f;

public:
	ABeta_Arcade_Team8GameModeBase();

	//UFUNCTION(BlueprintCallable)
	//void SetLevelTime(float time);

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION()
	void UpdateTimer();

	UFUNCTION(BlueprintCallable)
	void PauseTimer(bool paused);


	UFUNCTION(BlueprintCallable)
	float GetCurrentTimeSecconds() { return m_currentTimeSecconds; }

};
