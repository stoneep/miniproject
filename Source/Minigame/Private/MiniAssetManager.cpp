// Copyright NexonGames


#include "MiniAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "MiniGameplayTags.h"

UMiniAssetManager& UMiniAssetManager::Get()
{
	check(GEngine);

	UMiniAssetManager* MiniAssetManager = Cast<UMiniAssetManager>(GEngine->AssetManager);
	return *MiniAssetManager;
}

void UMiniAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FMiniGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data
	UAbilitySystemGlobals::Get().InitGlobalData();
}

