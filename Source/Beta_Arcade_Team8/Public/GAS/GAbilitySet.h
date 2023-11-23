// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "GAbilitySet.generated.h"

class UGAbilitySystemComponent;
class UGGameplayAbility;
/**
 *
 */
USTRUCT(BlueprintType)
struct FGAbilitySet_GameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FGAbilitySet_GrantedAbilityHandles
{
	GENERATED_BODY()
public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
};

UCLASS()
class BETA_ARCADE_TEAM8_API UGAbilitySet : public UDataAsset
{
	GENERATED_BODY()
public:
	void GiveToAbilitySystem(UGAbilitySystemComponent* InASC, FGAbilitySet_GrantedAbilityHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FGAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};
