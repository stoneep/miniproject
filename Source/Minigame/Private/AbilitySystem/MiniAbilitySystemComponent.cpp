// Copyright NexonGames


#include "AbilitySystem/MiniAbilitySystemComponent.h"

#include "MiniGameplayTags.h"

void UMiniAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMiniAbilitySystemComponent::EffectApplied);

	const FMiniGameplayTags& GameplayTags = FMiniGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Cyan,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_StreetCombatPower.ToString())
		);
}

void UMiniAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
