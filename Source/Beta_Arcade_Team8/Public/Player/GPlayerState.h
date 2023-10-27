// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GPlayerState.generated.h"

class UGAbilitySystemComponent;
/**
 *
 */
UCLASS()
class BETA_ARCADE_TEAM8_API AGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AGPlayerState();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY()
	UGAbilitySystemComponent* AbilitySystemComponent;
};
