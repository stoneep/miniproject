// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MiniDamageGameplayAbility.h"
#include "MiniProjectileSkill.generated.h"

class AMiniProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniProjectileSkill : public UMiniDamageGameplayAbility
{
	GENERATED_BODY()


protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMiniProjectile> ProjectileClass;
	
};
