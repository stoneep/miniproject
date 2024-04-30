// Copyright NexonGames


#include "Character/MiniEnemy.h"

#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"

AMiniEnemy::AMiniEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMiniAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UMiniAttributeSet>("AttributeSet");
}

void AMiniEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
