// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GPlayerController.h"
#include "Player/GPlayerCharacter.h"
#include "GAS/GAbilitySystemComponent.h"

UGAbilitySystemComponent* AGPlayerController::GetASC() const
{
	auto PC = Cast<AGPlayerCharacter>(GetCharacter());
	return CastChecked<UGAbilitySystemComponent>(PC->GetAbilitySystemComponent());
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
