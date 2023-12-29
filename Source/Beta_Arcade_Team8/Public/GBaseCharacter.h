// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GBaseCharacter.generated.h"

UCLASS()
class BETA_ARCADE_TEAM8_API AGBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGBaseCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UGAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSet> CharacterAttributeSet;
};
