// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GGameplayAbility.h"

#include "Player/GPlayerCharacter.h"

AGPlayerCharacter* UGGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	return (CurrentActorInfo ? Cast<AGPlayerCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}
