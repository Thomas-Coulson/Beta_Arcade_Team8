// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GPlayerController.generated.h"

class AGPlayerState;
class UGAbilitySystemComponent;
/**
 *
 */
UCLASS()
class BETA_ARCADE_TEAM8_API AGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "InputSystem|PlayerController")
	UGAbilitySystemComponent* GetASC() const;

protected:
	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};
