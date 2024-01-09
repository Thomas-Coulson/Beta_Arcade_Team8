// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSest/GPlayerAttributes.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffectExtension.h"
#include "Player/GPlayerCharacter.h"

void UGPlayerAttributes::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	AGPlayerCharacter* Player = CastChecked<AGPlayerCharacter>(GetOwningAbilitySystemComponent()->GetAvatarActor());
	if (Attribute == GetMaxJumpsAttribute())
	{
		Player->JumpMaxCount = NewValue;
	}
	else if (Attribute == GetZVelocityAttribute())
	{
		Player->GetCharacterMovement()->JumpZVelocity = NewValue;
	}
}
