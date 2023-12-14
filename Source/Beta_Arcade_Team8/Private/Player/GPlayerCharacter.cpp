// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "NativeGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/GAbilitySystemComponent.h"
#include "GAS/GAbilitySet.h"
#include "GAS/AttributeSest/GPlayerAttributes.h"
#include "Input/G_EIC.h"
#include "Player/GPlayerController.h"

//shortcus for logging debug outputs
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

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
	
	GetCharacterMovement()->AirControl = 1;
	GetCharacterMovement()->GravityScale = 1.4;
	GetCharacterMovement()->JumpZVelocity = 500;

	PlayerAttributeSet = CreateDefaultSubobject<UGPlayerAttributes>(TEXT("PlayerAttributes"));
}

void AGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UG_EIC* EIC = Cast<UG_EIC>(PlayerInputComponent);
	check(EIC);

	TArray<uint32> BindHandles;

	EIC->BindAbilityActions(InputConfig, this, &ThisClass::InputAbilityTagPressed, &ThisClass::InputAbilityTagReleased, BindHandles);

	EIC->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag("InputTag.Move"), ETriggerEvent::Triggered, this,
		&ThisClass::MoveForward);
	EIC->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag("InputTag.Look"), ETriggerEvent::Triggered, this,
		&ThisClass::Look);
}

void AGPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

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

	//TomC - allow plane constraints for wall running
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
}

void AGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* characterMovement = GetCharacterMovement();

	if (characterMovement->IsFalling())
	{
		//print("Is Falling");
		//TomC - Setup left and right Line Traces for Wall Running
		

		FVector TraceStart = GetActorLocation();
		FVector FrontTraceStart = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - FrontTraceOffset);
		FVector RightTraceEnd = TraceStart + GetActorRightVector() * TraceLength;
		FVector LeftTraceEnd = TraceStart - GetActorRightVector() * TraceLength;
		FVector FrontTraceEnd = FrontTraceStart + GetActorForwardVector() * TraceLength;

		FCollisionQueryParams RightQueryParams;
		RightQueryParams.AddIgnoredActor(this);

		FCollisionQueryParams LeftQueryParams;
		LeftQueryParams.AddIgnoredActor(this);

		FCollisionQueryParams FrontQueryParams;
		FrontQueryParams.AddIgnoredActor(this);


		//test front wall climb before wall run
		if (!RunningOnLeft && !RunningOnRight && (CurrentClimbs < MaxClimbs || ClimbingFront))
		{
			if (GetWorld()->LineTraceSingleByChannel(FrontHit, FrontTraceStart, FrontTraceEnd, FrontTraceChannelProperty, FrontQueryParams))
			{
				if (!FrontHit.GetActor()->ActorHasTag("NoClimb") && FrontHit.GetActor() != PreviousWall)
				{
					ClimbingFront = true;
					if (CurrentClimbs == 0)
					{
						CurrentClimbs++;
						StartClimbTimer();
					}

					//Set Rotation, movement, and gravity scale to stick to wall
					SetActorRotation(FRotator(0, FrontHit.Normal.Rotation().Yaw + 180, 0));
					characterMovement->Velocity = FVector(0, 0, GetActorUpVector().Z * 500);
					characterMovement->GravityScale = 0;
					//lock player to Z axis
					characterMovement->SetPlaneConstraintNormal(FVector(1, 1, 0));
				}
			}
			else
			{
				StopClimbTimer();
			}
		}

		if (!RunningOnLeft && !wallrunStopped)
		{
			if (GetWorld()->LineTraceSingleByChannel(RightHit, TraceStart, RightTraceEnd, RightTraceChannelProperty, RightQueryParams))
			{
				if (!JumpingOffWallRight && CurrentClimbs < MaxClimbs && RightHit.GetActor() != PreviousWall)
				{
					//Touching Right wall in the air (and not jumping off)
					if (!RunningOnRight)
						StartWallrunTimer();

					RunningOnRight = true;
					AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Ability.Jump.Override"));// <- Matthews magic

					//Set Rotation, movement, and gravity scale to stick to wall
					SetActorRotation(FRotator(0, RightHit.Normal.Rotation().Yaw + 90, 0));
					characterMovement->Velocity = FVector(GetActorForwardVector().X * 500, GetActorForwardVector().Y * 500, 0);
					characterMovement->GravityScale = 0;

					//lock player to Z axis
					characterMovement->SetPlaneConstraintNormal(FVector(0, 0, 1));
				}
			}
			else
			{
				JumpingOffWallRight = false;
				RunningOnRight = false;
				PlayerOffWall();
			}
		}

		if (!RunningOnRight && !wallrunStopped)
		{
			if (GetWorld()->LineTraceSingleByChannel(LeftHit, TraceStart, LeftTraceEnd, LeftTraceChannelProperty, LeftQueryParams))
			{
				if (!JumpingOffWallLeft && CurrentClimbs < MaxClimbs && LeftHit.GetActor() != PreviousWall)
				{
					//Touching Right wall in the air (and not jumping off)
					if (!RunningOnLeft)
						StartWallrunTimer();

					//Touching Left wall in the air
					RunningOnLeft = true;
					AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Ability.Jump.Override"));// <- Matthews magic

					//Set Rotation, movement, and gravity scale to stick to wall
					SetActorRotation(FRotator(0, LeftHit.Normal.Rotation().Yaw - 90, 0));
					characterMovement->Velocity = FVector(GetActorForwardVector().X * 500, GetActorForwardVector().Y * 500, 0);
					characterMovement->GravityScale = 0;

					//lock player to Z axis
					characterMovement->SetPlaneConstraintNormal(FVector(0, 0, 1));
				}
			}
			else
			{
				JumpingOffWallLeft = false;
				RunningOnLeft = false;
				PlayerOffWall();
			}
		}

		//Debug Draw for line trace
		//DrawDebugLine(GetWorld(), TraceStart, RightTraceEnd, RightHit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
		//DrawDebugLine(GetWorld(), TraceStart, LeftTraceEnd, LeftHit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
		//DrawDebugLine(GetWorld(), FrontTraceStart, FrontTraceEnd, FrontHit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	}
	else
	{
		PreviousWall = NULL;
		CurrentClimbs = 0;
		HasRunOnRight = false;
		wallrunStopped = false;
	}

}

void AGPlayerCharacter::StartClimbTimer()
{
	GetWorldTimerManager().SetTimer(ClimbTimerHandle, this, &AGPlayerCharacter::UpdateClimbTimer, ClimbUpdateTick, true, 0.0f);
}

void AGPlayerCharacter::UpdateClimbTimer()
{
	CurrentClimbDuration += ClimbUpdateTick;
	if (CurrentClimbDuration >= ClimbDuration)
	{
		StopClimbTimer();
	}
}

void AGPlayerCharacter::StopClimbTimer()
{
	if (GetWorldTimerManager().IsTimerActive(ClimbTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(ClimbTimerHandle);
	}

	CurrentClimbDuration = 0;
	ClimbingFront = false;
	PlayerOffWall();
}

void AGPlayerCharacter::StartWallrunTimer()
{
	GetWorldTimerManager().SetTimer(WallrunTimerHandle, this, &AGPlayerCharacter::UpdateWallrunTimer, WallrunUpdateTick, true, 0.0f);
}

void AGPlayerCharacter::UpdateWallrunTimer()
{
	CurrentWallrunDuration += WallrunUpdateTick;
	if (CurrentWallrunDuration >= WallrunDuration)
	{
		StopWallrunTimer();
	}
}

void AGPlayerCharacter::StopWallrunTimer()
{
	if (GetWorldTimerManager().IsTimerActive(WallrunTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(WallrunTimerHandle);
	}

	CurrentWallrunDuration = 0;
	wallrunStopped = true;
	RunningOnRight = false;
	RunningOnLeft = false;
	PlayerOffWall();
}

void AGPlayerCharacter::InputAbilityTagPressed(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void AGPlayerCharacter::InputAbilityTagReleased(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagReleased(InputTag);
}

float AGPlayerCharacter::LerpMovement()
{
	return FMath::Lerp(0.0f, 1.0f, moveLerpAlpha);
}

void AGPlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	//Add lerp to smoothly move from 0 to max speed (acceleration) rather than just move at max speed
	//reset when stopped 
	//also do this for left and right
	if (GetController())
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardVector, DirectionValue.Y * LerpMovement());

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, DirectionValue.X * LerpMovement());

		//will accellerate character when holding move input (currently doesnt reset when let go though)
		if (moveLerpAlpha < 1.0f)
		{
			moveLerpAlpha += playerAcceleration;
		}
		else
		{
			moveLerpAlpha = 1.0f;
		}
	}
}

void AGPlayerCharacter::Look(const FInputActionValue& Value)
{
	//added test comment
	//look player look when on a wall
	if (!IsPlayerOnWall())
	{
		const FVector2D LookVector = Value.Get<FVector2D>();
		if (GetController())
		{
			if (LookVector.X != 0.0f)
			{
				AddControllerYawInput(LookVector.X);
			}
			if (LookVector.Y != 0.0f)
			{
				AddControllerPitchInput(-LookVector.Y);
			}
		}
	}
	
}

void AGPlayerCharacter::PlayerOffWall()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->GravityScale = 1.4;
	MovementComponent->SetPlaneConstraintNormal(FVector(0, 0, 0));
	AbilitySystemComponent->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("Ability.Jump.Override"));
}
