// Copyright NexonGames


#include "Character/MiniEnemy.h"

#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
//#include "Minigame/Minigame.h"

AMiniEnemy::AMiniEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UMiniAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UMiniAttributeSet>("AttributeSet");
}

int32 AMiniEnemy::GetPlayerLevel()
{
	return Level;
}

void AMiniEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AMiniEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMiniAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
