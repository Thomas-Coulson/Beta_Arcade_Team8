// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSest/CharacterAttributeSet.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/GPlayerCharacter.h"

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	AGPlayerCharacter* Player = CastChecked<AGPlayerCharacter>(GetOwningAbilitySystemComponent()->GetAvatarActor());
	if (Attribute == GetSpeedMultiplierAttribute())
	{
		Player->GetCharacterMovement()->MaxWalkSpeed *= NewValue;
	}
}

