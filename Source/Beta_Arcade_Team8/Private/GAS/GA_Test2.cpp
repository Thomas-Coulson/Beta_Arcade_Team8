// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA_Test2.h"

UGA_Test2::UGA_Test2()
{
	ActivationPolicy = EGAbilityActivationPolicy::OnInputTriggered;
}

bool UGA_Test2::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGA_Test2::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Yellow, TEXT("HERE"));
}
