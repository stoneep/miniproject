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
	FGameplayTag Attributes_Primary_Stability; //안정치
	FGameplayTag Attributes_Primary_Accuracy; //명중치
	FGameplayTag Attributes_Primary_Evasion; //회피
	FGameplayTag Attributes_Primary_Crit; 
	FGameplayTag Attributes_Primary_CritDMG;
	FGameplayTag Attributes_Primary_Healing; //치유력
	FGameplayTag Attributes_Primary_NormalAttackRange; //사거리
	FGameplayTag Attributes_Primary_CrowdControlRES; //군중제어 강화
	FGameplayTag Attributes_Primary_CostRecovery;
	FGameplayTag Attributes_Primary_CrowdControlPower; //군중제어 저항
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

	
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	
	FGameplayTag Effects_HitReact;
	//FGameplayTag Effects_DieReact;
//1번
private:
	static FMiniGameplayTags GameplayTags;
};
