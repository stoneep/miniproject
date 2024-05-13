// Copyright NexonGames


#include "AbilitySystem/MiniAbilitySystemGlobals.h"

#include "MiniAbilityTypes.h"

FGameplayEffectContext* UMiniAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FMiniGameplayEffectContext;
}
