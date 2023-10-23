// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAbilitySet.h"
#include "GameplayAbilitySpecHandle.h"
#include "GAS/GAbilitySystemComponent.h"
#include "GAS/GGameplayAbility.h"

void FGAbilitySet_GrantedAbilityHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void UGAbilitySet::GiveToAbilitySystem(UGAbilitySystemComponent* InASC, FGAbilitySet_GrantedAbilityHandles* OutGrantedHandles,
	UObject* SourceObject) const
{
	check(InASC);
	if (!InASC->IsOwnerActorAuthoritative())
	{
		return;
	}
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FGAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		UGGameplayAbility* Ability = AbilityToGrant.Ability->GetDefaultObject<UGGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(Ability, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = InASC->GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}

