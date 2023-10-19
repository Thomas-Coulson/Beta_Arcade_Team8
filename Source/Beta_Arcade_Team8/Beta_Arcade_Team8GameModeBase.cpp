// Copyright Epic Games, Inc. All Rights Reserved.


#include "Beta_Arcade_Team8GameModeBase.h"

ABeta_Arcade_Team8GameModeBase::ABeta_Arcade_Team8GameModeBase()
{
	//Set defualts for gamemode
	DefaultPawnClass = APlayer_Pawn::StaticClass();
}

void ABeta_Arcade_Team8GameModeBase::SetLevelTime(float time)
{
	m_levelTimeLimit = time;
	m_currentTimeSecconds = m_levelTimeLimit;
}

void ABeta_Arcade_Team8GameModeBase::StartTimer()
{
	//Set a timer to call UpdateTimer every 1.0 seconds
	GetWorldTimerManager().SetTimer(m_levelTimerHandle, this, &ABeta_Arcade_Team8GameModeBase::UpdateTimer, 1.0f, true, 0.0f);
}

void ABeta_Arcade_Team8GameModeBase::UpdateTimer()
{
	m_currentTimeSecconds--;
	if (m_currentTimeSecconds <= 0)
	{
		GetWorldTimerManager().ClearTimer(m_levelTimerHandle);
	}
}

void ABeta_Arcade_Team8GameModeBase::PauseTimer(bool paused)
{
	if (paused)
	{
		GetWorldTimerManager().PauseTimer(m_levelTimerHandle);
	}
	else
	{
		GetWorldTimerManager().UnPauseTimer(m_levelTimerHandle);
	}
}
