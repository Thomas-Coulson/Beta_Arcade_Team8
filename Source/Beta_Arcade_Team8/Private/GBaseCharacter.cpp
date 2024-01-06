// Fill out your copyright notice in the Description page of Project Settings.


#include "GBaseCharacter.h"
#include "GAS/GAbilitySystemComponent.h"
#include "Player/GCharacterMovementComponent.h"

// Sets default values
AGBaseCharacter::AGBaseCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UGCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGAbilitySystemComponent>(TEXT("ASC"));
}

UAbilitySystemComponent* AGBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

// Called when the game starts or when spawned
void AGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

