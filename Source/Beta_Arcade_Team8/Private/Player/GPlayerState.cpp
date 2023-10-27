// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GPlayerState.h"
#include "GAS/GAbilitySystemComponent.h"

AGPlayerState::AGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* AGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
