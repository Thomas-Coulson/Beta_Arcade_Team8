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
		//playerCharacter = player;
		//print("Overlap Begin");
		//printFString("Overlapping Actor = %s", *OtherActor->GetName());
		playerLerping = true;
		playerInZone = true;
		climbUpActive = true;
		print("Started lerping");

		//FRotator playerRotation = player->GetActorRotation();
		//FRotator endPointRotation = endPoint->GetActorRotation();
		//player->SetActorRotation(FRotator(endPointRotation.Pitch, endPointRotation.Yaw, endPointRotation.Roll));

		UCharacterMovementComponent* MovementComponent = player->GetCharacterMovement();
		baseGravScale = MovementComponent->GravityScale;
		MovementComponent->GravityScale = 0;

		lerpAlpha = 0;
		StartLerpLoc = player->GetActorLocation();
		EndLerpLoc = StartLerpLoc;
		EndLerpLoc.Z = endPoint->GetActorLocation().Z;

		//int moveScalar = 50;
		//this will be split in 2 for actual movement and lerps
		//FVector newPos = player->GetActorLocation() + (player->GetActorForwardVector() * moveScalar);
		//FVector newPos = player->GetActorLocation();
		//newPos.Z = endPoint->GetActorLocation().Z;


		//player->SetActorLocation(newPos);
	}
}

void AClimbUpZone::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	//on end overlap, debug display (for now)
	//if overlapping actor == specified actor

	player = Cast<AGPlayerCharacter>(OtherActor);
	if (player)
	{
		//print("End Overlap");
		//printFString(" %s has left the overlap", *OtherActor->GetName());
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

		/*FString debugText = FString("angle = ") + FString::SanitizeFloat(angle);
		print(debugText);

		FString debugText2 = FString("Player Yaw = ") + FString::SanitizeFloat(player->GetActorRotation().Yaw);
		print(debugText2);*/

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

// Called when the game starts or when spawned
void AClimbUpZone::BeginPlay()
{
	Super::BeginPlay();

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
			if (lerpAlpha >= 1.0)
			{
				print("stopped lerping");
				UCharacterMovementComponent* MovementComponent = player->GetCharacterMovement();
				MovementComponent->GravityScale = baseGravScale;
				playerLerping = false;

				//push player forwards after verticle movement
				player->LaunchCharacter(player->GetActorForwardVector() * 200, true, false);

				climbUpActive = false;
			}
			else
			{
				lerpAlpha += lerpAphaMultiplier;
			}

			if (playerLerping)
			{
				player->GetController()->SetControlRotation(FRotator(playerRotation.Pitch, endPoint->GetActorRotation().Yaw, playerRotation.Roll));
				lerpActorToPos(player);
			}

			
		}
		
		
	}
	
}

