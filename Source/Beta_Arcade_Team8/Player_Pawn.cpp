// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Pawn.h"

// Sets default values
APlayer_Pawn::APlayer_Pawn()
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
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);

	

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

