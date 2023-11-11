// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "ClimbUpZone.h"
#include "Math/UnrealMathVectorCommon.h"

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
	if (player)
	{
		//playerCharacter = player;
		//print("Overlap Begin");
		//printFString("Overlapping Actor = %s", *OtherActor->GetName());
		playerLerping = true;
		playerInZone = true;
		print("Started lerping");

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

void AClimbUpZone::lerpActorToPos(AActor* actor, FVector newPos)
{
	actor->SetActorLocation(FMath::Lerp(actor->GetActorLocation(), newPos, 0.2));
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
		print("Player Valid");
		//FVector newPos = player->GetActorLocation();
		//newPos.Z = endPoint->GetActorLocation().Z;
		FVector newPos = endPoint->GetActorLocation();

		//this if needs updating to stop the lerp at the right time
		if (player->GetActorLocation().Z >= newPos.Z)
		{
			print("stopped lerping");
			playerLerping = false;
		}

		if (playerLerping)
		{
			print("Lerping");
			lerpActorToPos(player, newPos);
		}
	}
	
	

}

