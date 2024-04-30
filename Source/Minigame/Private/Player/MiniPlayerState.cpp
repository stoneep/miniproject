// Copyright NexonGames


#include "Player/MiniPlayerState.h"

#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"

AMiniPlayerState::AMiniPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMiniAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UMiniAttributeSet>("AttributeSet");
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AMiniPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
