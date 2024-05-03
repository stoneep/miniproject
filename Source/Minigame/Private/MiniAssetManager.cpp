// Copyright NexonGames


#include "MiniAssetManager.h"
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
}

