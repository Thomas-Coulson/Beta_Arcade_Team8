// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GBaseCharacter.h"
#include "InputActionValue.h"
#include "GAS/GAbilitySet.h"
#include "Input/GInputConfig.h"
#include "GPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 *
 */
UCLASS()
class BETA_ARCADE_TEAM8_API AGPlayerCharacter : public AGBaseCharacter
{
	GENERATED_BODY()

public:
	AGPlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;

	void InputAbilityTagPressed(FGameplayTag InputTag);
	void InputAbilityTagReleased(FGameplayTag InputTag);

	virtual void OnRep_PlayerState() override;

	void MoveForward(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputSystem")
	UGAbilitySet* AbilitySet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputSystem")
	UGInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputSystem")
	class UInputMappingContext* DefaultMappingContext;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USkeletalMeshComponent> SkelMeshComp = nullptr;

	UPROPERTY(EditAnywhere)
	float ArmLength = 300;

protected:

	TWeakObjectPtr<class UGPlayerAttributes> PlayerAttributeSet;
};
