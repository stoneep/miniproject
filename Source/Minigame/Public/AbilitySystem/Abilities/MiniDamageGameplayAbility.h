// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MiniGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "MiniDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniDamageGameplayAbility : public UMiniGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	// FScalableFloat Damage;

	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
};
