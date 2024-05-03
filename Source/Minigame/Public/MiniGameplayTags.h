// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * MiniGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FMiniGameplayTags
{
public:
	static const FMiniGameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();


	FGameplayTag Attributes_Primary_ATK;
	FGameplayTag Attributes_Primary_DEF;
	FGameplayTag Attributes_Primary_Dodge;
	FGameplayTag Attributes_Primary_HIT;
	FGameplayTag Attributes_Primary_Block;
	FGameplayTag Attributes_Primary_Crit;
	FGameplayTag Attributes_Primary_CritDMG;
	FGameplayTag Attributes_Primary_Healing;

	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_OutdoorCombatPower;
	FGameplayTag Attributes_Secondary_IndoorCombatPower;
	FGameplayTag Attributes_Secondary_StreetCombatPower;
protected:

private:
	static FMiniGameplayTags GameplayTags;
};
