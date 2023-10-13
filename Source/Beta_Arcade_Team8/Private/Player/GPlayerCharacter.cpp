// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "NativeGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/GAbilitySystemComponent.h"
#include "GAS/GAbilitySet.h"
#include "Input/G_EIC.h"
#include "Player/GPlayerState.h"
#include "Player/GPlayerController.h"


AGPlayerCharacter::AGPlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TomC - create a new player skeletal mesh and attach it
	SkelMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player Skeletal Mesh"));
	SkelMeshComp->SetupAttachment(RootComponent);

	//TomC - create a new player cam spring arm, and attach it to the mesh
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Player Cam Spring Arm"));
	SpringArmComp->SetupAttachment(SkelMeshComp);

	//Setting default properties of the SpringArmComp
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = ArmLength;

	//TomC - create a new player camera, and attach it to the spring arm
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
}

void AGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UG_EIC* EIC = Cast<UG_EIC>(PlayerInputComponent);
	check(EIC);

	TArray<uint32> BindHandles;

	EIC->BindAbilityActions(InputConfig, this, &ThisClass::InputAbilityTagPressed, &ThisClass::InputAbilityTagReleased, BindHandles);

	EIC->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag("InputTag.Move"), ETriggerEvent::Triggered, this,
		&ThisClass::Move);
	EIC->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag("InputTag.Look"), ETriggerEvent::Triggered, this,
		&ThisClass::Look);
}

void AGPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AGPlayerState* PS = Cast<AGPlayerState>(GetPlayerState());
	check(PS);

	AbilitySystemComponent = Cast<UGAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	AbilitySystemComponent->InitAbilityActorInfo(PS, this);

	if(AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent.Get(), nullptr, this);
	}
}

void AGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(AGPlayerController* PC = Cast<AGPlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AGPlayerCharacter::InputAbilityTagPressed(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void AGPlayerCharacter::InputAbilityTagReleased(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagReleased(InputTag);
}

void AGPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AGPlayerState* PS = Cast<AGPlayerState>(GetPlayerState());
	check(PS);

	AbilitySystemComponent = Cast<UGAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS,this);

	if(AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent.Get(), nullptr, this);
	}
}

void AGPlayerCharacter::Move(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Yellow, TEXT("MOVE"));
}

void AGPlayerCharacter::Look(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Yellow, TEXT("LOOK"));
}