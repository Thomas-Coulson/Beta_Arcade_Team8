// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GGameplayAbility.h"
#include "GJumpAbility.generated.h"

/**
 *
 */
UCLASS()
class BETA_ARCADE_TEAM8_API UGJumpAbility : public UGGameplayAbility
{
	GENERATED_BODY()

public:
	UGJumpAbility();

protected:

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StartJump();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void StopJump();

private:

	float WallJumpMultiplier = 450;
};
