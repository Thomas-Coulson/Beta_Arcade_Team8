// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSest/GPlayerAttributes.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Player/GPlayerCharacter.h"

void UGPlayerAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Cyan, TEXT("HERE"));
	AGPlayerCharacter* Player = Cast<AGPlayerCharacter>(GetOwningActor());
	if (Attribute == GetMaxJumpsAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		Player->JumpMaxCount = NewValue;
	}
	else if (Attribute == GetZVelocityAttribute())
	{
		Player->GetCharacterMovement()->JumpZVelocity = NewValue;
	}
}

void UGPlayerAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);
	AGPlayerCharacter* Player = Cast<AGPlayerCharacter>(GetOwningActor());
	if (Data.EvaluatedData.Attribute == GetMaxJumpsAttribute())
	{
		Player->JumpMaxCount = Data.EvaluatedData.Magnitude;
	}
}
