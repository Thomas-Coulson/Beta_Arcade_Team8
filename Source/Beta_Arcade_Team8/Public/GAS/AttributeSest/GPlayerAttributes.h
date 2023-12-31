// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GPlayerAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 *
 */
UCLASS()
class BETA_ARCADE_TEAM8_API UGPlayerAttributes : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Jump")
	FGameplayAttributeData MaxJumps = 1.0f;
	ATTRIBUTE_ACCESSORS(UGPlayerAttributes, MaxJumps)

	UPROPERTY(BlueprintReadOnly, Category = "Jump")
	FGameplayAttributeData ZVelocity = 500.f;
	ATTRIBUTE_ACCESSORS(UGPlayerAttributes, ZVelocity)

	UPROPERTY(BlueprintReadOnly, Category = "SpeedMultiplier")
	FGameplayAttributeData SpeedMultiplier = 1.0f;
	ATTRIBUTE_ACCESSORS(UGPlayerAttributes, SpeedMultiplier)

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
