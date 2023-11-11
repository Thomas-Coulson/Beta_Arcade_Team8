// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "ClimbUpZone.generated.h"

UCLASS()
class BETA_ARCADE_TEAM8_API AClimbUpZone : public ATriggerBox
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClimbUpZone();

	//AGPlayerCharacter* playerCharacter;
	
	UPROPERTY(EditAnywhere)
	class AActor* endPoint;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void lerpActorToPos(AActor* actor);
	bool isPlayerLookingAtEndPoint();
	float getAngleBetweenVectors(FVector A, FVector B);
	float DotProduct(FVector A, FVector B);
	float VectorMagnitude(FVector A);

	bool playerInZone = false;
	bool playerLerping = false;
	float baseGravScale;
	float lerpAlpha = 0;
	float lerpAphaMultiplier = 0.01;
	class AGPlayerCharacter* player;

	//FVector WallDirection = endPoint->GetActorLocation() - this->GetActorLocation();

	bool climbUpActive = false;

	FVector StartLerpLoc;
	FVector EndLerpLoc;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
