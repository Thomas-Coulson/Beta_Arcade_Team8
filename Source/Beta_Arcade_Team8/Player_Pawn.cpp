// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Pawn.h"

// Sets default values
APlayer_Pawn::APlayer_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TomC - create a new player camera and attach it
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APlayer_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

