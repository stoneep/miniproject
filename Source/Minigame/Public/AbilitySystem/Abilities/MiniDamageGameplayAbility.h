// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MiniGameplayAbility.h"
#include "MiniDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniDamageGameplayAbility : public UMiniGameplayAbility
{
	GENERATED_BODY()


protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	// FScalableFloat Damage;

	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
