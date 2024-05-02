// Copyright NexonGames


#include "Player/MiniPlayerState.h"

#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "Net/UnrealNetwork.h"

AMiniPlayerState::AMiniPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMiniAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UMiniAttributeSet>("AttributeSet");
	NetUpdateFrequency = 100.f;
}

void AMiniPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMiniPlayerState, Level);
}

UAbilitySystemComponent* AMiniPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMiniPlayerState::OnRep_Level(int32 OldLevel)
{
}
