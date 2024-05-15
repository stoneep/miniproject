// Copyright NexonGames


#include "MiniGameplayTags.h"
#include "GameplayTagsManager.h"

FMiniGameplayTags FMiniGameplayTags::GameplayTags;

void FMiniGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_ATK = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.ATK"),
			FString("Striking power"));
	GameplayTags.Attributes_Primary_DEF = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.DEF"),
				FString("Defensive power"));
	GameplayTags.Attributes_Primary_Accuracy = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.Accuracy"),
					FString("Hit the target"));
	GameplayTags.Attributes_Primary_Evasion = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.Evasion"),
					FString("Dodge/Avoid"));
	GameplayTags.Attributes_Primary_Stability = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.Stability"),
					FString("Ignore Damage"));
	GameplayTags.Attributes_Primary_Crit = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.Crit"),
					FString("Critical"));
	GameplayTags.Attributes_Primary_CritDMG = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.CritDMG"),
					FString("CriticalDMG"));
	GameplayTags.Attributes_Primary_Healing = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.Healing"),
					FString("Healing"));
	GameplayTags.Attributes_Primary_NormalAttackRange = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.NormalAttackRange"),
					FString("NormalAttackRange"));
	GameplayTags.Attributes_Primary_CrowdControlPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.CrowdControlPower"),
					FString("CrowdControlPower"));
	GameplayTags.Attributes_Primary_CrowdControlRES = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.CrowdControlRES"),
					FString("CrowdControlRES"));
	GameplayTags.Attributes_Primary_CostRecovery = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.CostRecovery"),
					FString("CostRecovery"));
	GameplayTags.Attributes_Primary_RelationshipRank = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.RelationshipRank"),
					FString("RelationshipRank"));
	GameplayTags.Attributes_Primary_BonusRecipients = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.BonusRecipients"),
					FString("BonusRecipients"));
	//
	GameplayTags.Attributes_Secondary_OutdoorCombatPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.OutdoorCombatPower"),
		FString("OutDoorATK"));
	GameplayTags.Attributes_Secondary_StreetCombatPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.StreetCombatPower"),
		FString("StreetCombatATK"));
	GameplayTags.Attributes_Secondary_IndoorCombatPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.IndoorCombatPower"),
		FString("IndoorCombatATK"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("MaxHealth"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("MaxMana"));

	/*
	 * InputTags
	 */
	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.LMB"),
			FString("LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.RMB"),
			FString("RMB"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.1"),
			FString("Key 1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.2"),
			FString("Key 2"));
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.3"),
			FString("Key 3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.4"),
			FString("Key 4"));

	/*
	 * Tags
	 */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage"),
		FString("Damage"));
	
	GameplayTags.Damage_Bullet = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Bullet"),
		FString("Fire Damage Type")
		);
	//GameplayTags.DamageTypes.Add(GameplayTags.Damage_Bullet);
	
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Lightning"),
			FString("Lightning Damage Type")
			);
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"),
		FString("Arcane Damage Type")
		);
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
		);
	
	/*
	* Damage Types
	*/
	
	GameplayTags.Attributes_Resistance_Bullet = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Attributes.Resistance.Bullet"),
				FString("Resistance to Bullet damage")
				);
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Resistance.Arcane"),
			FString("Resistance to Arcane damage")
			);
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("Resistance to Lightning damage")
		);
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("Resistance to Physical damage")
		);

	/*
	 * Map of Damage Types to Resistances
	 */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Bullet, GameplayTags.Attributes_Resistance_Bullet);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);


	/*
	 * Effects
	*/
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Effects.HitReact"),
		FString("Effects_HitReact"));
	// GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	// 		FName("Effects.DieReact"),
	// 	FString("Effects_DieReact"));

	/*
	 * Abilities
	*/
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Attack"),
		FString("Abilities_Attack"));
	
}
