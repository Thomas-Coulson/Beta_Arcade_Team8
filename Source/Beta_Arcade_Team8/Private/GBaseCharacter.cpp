// Fill out your copyright notice in the Description page of Project Settings.


#include "GBaseCharacter.h"
#include "GAS/GAbilitySystemComponent.h"

// Sets default values
AGBaseCharacter::AGBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
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

