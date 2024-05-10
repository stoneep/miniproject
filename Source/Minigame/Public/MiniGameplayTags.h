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
	FGameplayTag Attributes_Primary_Stability;
	FGameplayTag Attributes_Primary_Accuracy;
	FGameplayTag Attributes_Primary_Evasion;
	FGameplayTag Attributes_Primary_Crit;
	FGameplayTag Attributes_Primary_CritDMG;
	FGameplayTag Attributes_Primary_Healing;
	FGameplayTag Attributes_Primary_NormalAttackRange;
	FGameplayTag Attributes_Primary_CrowdControlRES;
	FGameplayTag Attributes_Primary_CostRecovery;
	FGameplayTag Attributes_Primary_CrowdControlPower;
	FGameplayTag Attributes_Primary_RelationshipRank;
	FGameplayTag Attributes_Primary_BonusRecipients;

	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_OutdoorCombatPower;
	FGameplayTag Attributes_Secondary_IndoorCombatPower;
	FGameplayTag Attributes_Secondary_StreetCombatPower;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
//1번
private:
	static FMiniGameplayTags GameplayTags;
};
