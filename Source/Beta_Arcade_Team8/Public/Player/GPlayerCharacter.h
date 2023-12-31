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

UCLASS()
class BETA_ARCADE_TEAM8_API AGPlayerCharacter : public AGBaseCharacter
{
	GENERATED_BODY()

public:
	AGPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	//TomC - Variable Access for wall running
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsPlayerOnWall() { return RunningOnLeft || RunningOnRight || ClimbingFront; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool PlayerOnLeftWall() { return RunningOnLeft; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool PlayerOnRightWall() { return RunningOnRight; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool PlayerClimbing() { return ClimbingFront; }

	void SetLeftWallJump(bool jumping) { JumpingOffWallLeft = jumping; }
	void SetRightWallJump(bool jumping) { JumpingOffWallRight = jumping; }
	void SetCurrentClimbs(int newClimbs) { CurrentClimbs = newClimbs; }
	void SetWallrunStopped(bool wallrunIsStopped) { wallrunStopped = wallrunIsStopped; }

	void SetPreviousWall(AActor* prevWall) { PreviousWall = prevWall; }
	FHitResult GetFrontHitResult() { return FrontHit; }
	FHitResult GetLeftHitResult() { return LeftHit; }
	FHitResult GetRightHitResult() { return RightHit; }

	void StopWallrunTimer();
	
protected:
	virtual void BeginPlay() override;

	void InputAbilityTagPressed(FGameplayTag InputTag);
	void InputAbilityTagReleased(FGameplayTag InputTag);
	float LerpMovement();
	void MoveForward(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void PlayerOffWall();
	void StartClimbTimer();
	void UpdateClimbTimer();
	void StopClimbTimer();

	void StartWallrunTimer();
	void UpdateWallrunTimer();

	void StartAccTimer();
	void UpdateAccTimer();
	void ResetAccTimer();

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

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> FrontTraceChannelProperty = ECC_Pawn;

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

	UPROPERTY(EditAnywhere)
	double FrontTraceOffset = 0.0f;

	UPROPERTY(EditAnywhere)
	float ClimbSpeed = 350.0f;

	UPROPERTY(EditAnywhere)
	float WallRunSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	int MaxClimbs = 1;

	UPROPERTY(EditAnywhere)
	float ClimbDuration = 1.0f;

	UPROPERTY(EditAnywhere)
	float WallrunDuration = 2.0f;

	UPROPERTY(EditAnywhere)
	float playerAcceleration = 0.005;

	float moveLerpAlpha = 0;
	bool isMoving = false;

	FTimerHandle AccelerationTimerHandle;
	float timeSinceLastMoveInput = 0;
	float AccUpdateTick = 0.001f;

	FVector2D CurrentDirectionValue;

	//Tomc- WallRun Variables
	bool RunningOnLeft = false;
	bool RunningOnRight = false;
	bool JumpingOffWallLeft = false;
	bool JumpingOffWallRight = false;
	bool HasRunOnRight = false;
	AActor* PreviousWall;
	FHitResult RightHit;
	FHitResult LeftHit;
	FHitResult FrontHit;

	FTimerHandle WallrunTimerHandle;
	float CurrentWallrunDuration = 0.0f;
	float WallrunUpdateTick = 0.5f;

	bool wallrunStopped = false;

	//TomC Wall Climb Variables
	bool ClimbingFront = false;
	int CurrentClimbs = 0;
	FTimerHandle ClimbTimerHandle;
	float CurrentClimbDuration = 0.0f;
	float ClimbUpdateTick = 0.5f;
};
