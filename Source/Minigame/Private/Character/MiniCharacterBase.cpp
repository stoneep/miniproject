// Copyright NexonGames


#include "Character/MiniCharacterBase.h"


AMiniCharacterBase::AMiniCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

UAbilitySystemComponent* AMiniCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AMiniCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


