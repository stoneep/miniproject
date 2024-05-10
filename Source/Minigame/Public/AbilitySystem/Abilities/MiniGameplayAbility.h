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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;
	
};
