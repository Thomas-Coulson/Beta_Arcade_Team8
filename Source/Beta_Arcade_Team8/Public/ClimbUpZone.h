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
	
	UPROPERTY(EditAnywhere)
	class AActor* endPoint;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	class AActor* SpecificActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
