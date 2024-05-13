// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "MiniAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;	
};
