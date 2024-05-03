// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MiniAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UMiniAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
	
};
