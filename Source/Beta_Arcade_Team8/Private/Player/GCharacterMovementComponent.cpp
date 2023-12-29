// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/GCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "GBaseCharacter.h"
#include "GAS/AttributeSest/GPlayerAttributes.h"

float UGCharacterMovementComponent::GetMaxSpeed() const
{
	AGBaseCharacter* Owner = Cast<AGBaseCharacter>(GetOwner());
	float Multiplier = Owner->GetAbilitySystemComponent()->GetNumericAttribute(UGPlayerAttributes::GetSpeedMultiplierAttribute());
	return Super::GetMaxSpeed() * Multiplier;
}
