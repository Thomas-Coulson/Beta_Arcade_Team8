// Fill out your copyright notice in the Description page of Project Settings.

#include "ClimbUpZone.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathVectorCommon.h"
#include "GameFramework/CharacterMovementComponent.h"

#include <string>
#include <cmath>
#include <Player/GPlayerCharacter.h>

//shortcus for logging debug outputs
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

// Sets default values
AClimbUpZone::AClimbUpZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &AClimbUpZone::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AClimbUpZone::OnOverlapEnd);
}

void AClimbUpZone::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	//on overlap, debug display (for now)
	//if overlapping actor == specified actor

	player = Cast<AGPlayerCharacter>(OtherActor);
	if (player && !climbUpActive && isPlayerLookingAtEndPoint())
	{
		//start player moving up wall
		playerLerping = true;
		playerInZone = true;
		climbUpActive = true;

		//claculate the player distance and speed to climb wall at
		float playerDistance = abs(endPoint->GetActorLocation().Z - player->GetActorLocation().Z);
		lerpAphaMultiplier = claculateLerpAlphaMultiplier(playerDistance);

		//disable gravbity for the player
		UCharacterMovementComponent* MovementComponent = player->GetCharacterMovement();
		baseGravScale = MovementComponent->GravityScale;
		MovementComponent->GravityScale = 0;

		//set bounds for the lerp movement
		lerpAlpha = 0;
		StartLerpLoc = player->GetActorLocation();
		EndLerpLoc = StartLerpLoc;
		EndLerpLoc.Z = endPoint->GetActorLocation().Z;
	}
}

void AClimbUpZone::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	//if overlapping actor == specified actor

	player = Cast<AGPlayerCharacter>(OtherActor);
	if (player)
	{
		playerInZone = false;
	}

}

void AClimbUpZone::lerpActorToPos(AActor* actor)
{
	actor->SetActorLocation(FMath::Lerp(StartLerpLoc, EndLerpLoc, lerpAlpha));
}

bool AClimbUpZone::isPlayerLookingAtEndPoint()
{
	if (player && endPoint)
	{
		FVector a = endPoint->GetActorForwardVector();
		FVector b = player->GetActorForwardVector();

		float angle = getAngleBetweenVectors(a, b);

		if (angle < 1.2)
			return true;
		else
			return false;
	}

	return false;
}

float AClimbUpZone::getAngleBetweenVectors(FVector A, FVector B)
{
	return acos((DotProduct(A, B) / (VectorMagnitude(A) * VectorMagnitude(B))));;
}

float AClimbUpZone::DotProduct(FVector A, FVector B)
{
	return ((A.X * B.X) + (A.Y * B.Y) + (A.Z * B.Z));
}

float AClimbUpZone::VectorMagnitude(FVector A)
{
	return sqrt(pow(A.X, 2) + pow(A.Y, 2) + pow(A.Z, 2));
}

float AClimbUpZone::claculateLerpAlphaMultiplier(float playerDistance)
{
	float x = ((playerDistance - minPlayerDist) / (maxPlayerDist - minPlayerDist));
	float y = 1 - x;
	return (minLerpAphaMultiplier * (y * 10));
}

// Called when the game starts or when spawned
void AClimbUpZone::BeginPlay()
{
	Super::BeginPlay();

	if(toggleDebugView)
		DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Magenta, true, -1, 0, 5);
}

// Called every frame
void AClimbUpZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (player)
	{
		FRotator playerRotation = player->GetActorRotation();

		if (climbUpActive)
		{
			//if at endpoint
			if (lerpAlpha >= 1.0)
			{
				//reset player gravity
				UCharacterMovementComponent* MovementComponent = player->GetCharacterMovement();
				MovementComponent->GravityScale = baseGravScale;
				playerLerping = false;

				//push player forwards after verticle movement
				player->LaunchCharacter(player->GetActorForwardVector() * lunchSpeed, true, false);

				climbUpActive = false;
			}
			else
			{
				lerpAlpha += lerpAphaMultiplier;
			}

			if (playerLerping)
			{
				//move player up wall vertically
				player->GetController()->SetControlRotation(FRotator(playerRotation.Pitch, endPoint->GetActorRotation().Yaw, playerRotation.Roll));
				lerpActorToPos(player);
			}
		}
	}
}

