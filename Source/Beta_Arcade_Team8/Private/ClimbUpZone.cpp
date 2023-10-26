// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "ClimbUpZone.h"

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
	
	AGPlayerCharacter* player = Cast<AGPlayerCharacter>(OtherActor);
	if (player)
	{
		print("Overlap Begin");
		printFString("Overlapping Actor = %s", *OtherActor->GetName());
	}

	/*if (OtherActor && (OtherActor != this) && OtherActor == SpecificActor)
	{
		print("Overlap Begin");
		printFString("Overlapping Actor = %s", *OtherActor->GetName());
	}*/
}

void AClimbUpZone::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	//on end overlap, debug display (for now)
	//if overlapping actor == specified actor

	AGPlayerCharacter* player = Cast<AGPlayerCharacter>(OtherActor);
	if (player)
	{
		print("End Overlap");
		printFString(" %s has left the overlap", *OtherActor->GetName());
	}
	
	/*if (OtherActor && (OtherActor != this) && OtherActor == SpecificActor)
	{
		print("End Overlap");
		printFString(" %s has left the overlap", *OtherActor->GetName());
	}*/
}

// Called when the game starts or when spawned
void AClimbUpZone::BeginPlay()
{
	Super::BeginPlay();

	//extent is too small / 0 (this needs to be bigger / update in editor)
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(100, 100, 100), FColor::Magenta, true, -1, 0, 5);
}

// Called every frame
void AClimbUpZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

