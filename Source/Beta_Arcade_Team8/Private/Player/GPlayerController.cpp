// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GPlayerController.h"

#include "GAS/GAbilitySystemComponent.h"
#include "Player/GPlayerState.h"

AGPlayerState* AGPlayerController::GetPlayerState() const
{
	return CastChecked<AGPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UGAbilitySystemComponent* AGPlayerController::GetASC() const
{
	return CastChecked<UGAbilitySystemComponent>(GetPlayerState()->GetAbilitySystemComponent());
}

void AGPlayerController::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PreProcessInput(DeltaTime, bGamePaused);
}

void AGPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if(UGAbilitySystemComponent* ASC = GetASC())
	{
		ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
