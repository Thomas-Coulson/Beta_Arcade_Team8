// Fill out your copyright notice in the Description page of Project Settings.


#include "GAssetManager.h"

#include "AbilitySystemGlobals.h"

void UGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
