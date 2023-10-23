// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GAssetManager.generated.h"

/**
 *
 */
UCLASS()
class BETA_ARCADE_TEAM8_API UGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	virtual void StartInitialLoading() override;
};
