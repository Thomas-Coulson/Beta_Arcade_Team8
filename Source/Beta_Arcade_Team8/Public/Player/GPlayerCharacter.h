// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GAS/GAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
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

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	//TomC - Variable Access for wall running
	bool IsPlayerOnWall() { return RunningOnLeft || RunningOnRight; }
	bool PlayerOnLeftWall() { return RunningOnLeft; }
	bool PlayerOnRightWall() { return RunningOnRight; }
	void SetLeftWallJump(bool jumping) { JumpingOffWallLeft = jumping; }
	void SetRightWallJump(bool jumping) { JumpingOffWallRight = jumping; }
	
protected:
	virtual void BeginPlay() override;

	void InputAbilityTagPressed(FGameplayTag InputTag);
	void InputAbilityTagReleased(FGameplayTag InputTag);

	void MoveForward(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void PlayerOffWall();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputSystem")
	UGAbilitySet* AbilitySet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputSystem")
	UGInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputSystem")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlayerAttributes")
	class UGPlayerAttributes* PlayerAttributeSet;

	UPROPERTY(EditAnywhere, Category="Collision")
	TEnumAsByte<ECollisionChannel> RightTraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> LeftTraceChannelProperty = ECC_Pawn;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USkeletalMeshComponent> SkelMeshComp = nullptr;

	UPROPERTY(EditAnywhere)
	float ArmLength = 300;

	UPROPERTY(EditAnywhere)
	float TraceLength = 50.0f;

	//Tomc- WallRun Variables
	bool RunningOnLeft = false;
	bool RunningOnRight = false;
	bool JumpingOffWallLeft = false;
	bool JumpingOffWallRight = false;
};
