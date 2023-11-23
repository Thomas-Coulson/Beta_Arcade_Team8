// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GGameplayAbility.generated.h"

/**
 *
 */

class AGPlayerCharacter;

UENUM(BlueprintType)
enum class EGAbilityActivationPolicy : uint8
{
	OnInputTriggered,
	WhileInputActive
};

UCLASS()
class BETA_ARCADE_TEAM8_API UGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	EGAbilityActivationPolicy GetActivationPolicy() const {return ActivationPolicy;}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Activation")
	EGAbilityActivationPolicy ActivationPolicy;

	AGPlayerCharacter* GetPlayerCharacterFromActorInfo();
};
