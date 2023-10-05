// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Player_Pawn.generated.h"

UCLASS()
class BETA_ARCADE_TEAM8_API APlayer_Pawn : public APawn
{
	GENERATED_BODY()

private:
	//TomC - camera component
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UCameraComponent> CameraComp = nullptr;

	UPROPERTY(EditAnywhere, Category = "Player | Camera")
	FVector DefaultCamlocation;

public:
	// Sets default values for this pawn's properties
	APlayer_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
