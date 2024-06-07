// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MiniGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	virtual FString GetDescription(int32 Level);
	virtual FString GetNextLevelDescription(int32 Level);
	static FString GetLockedDescription(int32 Level);
};
