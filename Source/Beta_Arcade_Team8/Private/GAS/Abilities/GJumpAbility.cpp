// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/GJumpAbility.h"
#include "Player/GPlayerCharacter.h"

UGJumpAbility::UGJumpAbility()
{
	ActivationPolicy = EGAbilityActivationPolicy::OnInputTriggered;
}

bool UGJumpAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	const AGPlayerCharacter* PlayerCharacter = Cast<AGPlayerCharacter>(ActorInfo->AvatarActor.Get());

	if (PlayerCharacter && Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		if (PlayerCharacter->CanJump())
		{
			return true;
		}
	}
	return false;
}

void UGJumpAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	StopJump();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGJumpAbility::StartJump()
{
	if (AGPlayerCharacter* PlayerCharacter = GetPlayerCharacterFromActorInfo())
	{
		PlayerCharacter->Jump();
	}
}

void UGJumpAbility::StopJump()
{
	if (AGPlayerCharacter* PlayerCharacter = GetPlayerCharacterFromActorInfo())
	{
		PlayerCharacter->StopJumping();
	}
}

