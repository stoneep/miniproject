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
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.3"),
			FString("Key 3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.4"),
			FString("Key 4"));
	GameplayTags.InputTag_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.5"),
			FString("Key 5"));
	GameplayTags.InputTag_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.6"),
			FString("Key 6"));
	GameplayTags.InputTag_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.7"),
			FString("Key 7"));
	GameplayTags.InputTag_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.8"),
			FString("Key 8"));
	GameplayTags.InputTag_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.9"),
			FString("Key 9"));
	GameplayTags.InputTag_0 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.0"),
			FString("Key 0"));
	GameplayTags.InputTag_q = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.q"),
			FString("Key q"));
	GameplayTags.InputTag_e = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.e"),
			FString("Key e"));
	GameplayTags.InputTag_r = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.r"),
			FString("Key r"));
	GameplayTags.InputTag_t = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.t"),
			FString("Key t"));
	GameplayTags.InputTag_y = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.y"),
			FString("Key y"));
	GameplayTags.InputTag_u = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.u"),
			FString("Key u"));
	GameplayTags.InputTag_i = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.i"),
			FString("Key i"));
	GameplayTags.InputTag_o = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.o"),
			FString("Key o"));
	GameplayTags.InputTag_p = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.p"),
			FString("Key p"));
	GameplayTags.InputTag_f = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.f"),
			FString("Key f"));
	GameplayTags.InputTag_g = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.g"),
			FString("Key g"));
	GameplayTags.InputTag_h = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.h"),
			FString("Key h"));
	GameplayTags.InputTag_j = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.j"),
			FString("Key j"));
	GameplayTags.InputTag_k = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.k"),
			FString("Key k"));
	GameplayTags.InputTag_l = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.l"),
			FString("Key l"));
	GameplayTags.InputTag_z = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.z"),
			FString("Key z"));
	GameplayTags.InputTag_x = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.x"),
			FString("Key x"));
	GameplayTags.InputTag_c = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.c"),
			FString("Key c"));
	GameplayTags.InputTag_v = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.v"),
			FString("Key v"));
	GameplayTags.InputTag_b = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.b"),
			FString("Key b"));
	GameplayTags.InputTag_n = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.n"),
			FString("Key n"));
	GameplayTags.InputTag_m = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.m"),
			FString("Key m"));
	GameplayTags.InputTag_L_ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.L_ctrl"),
			FString("Key L_ctrl"));
	GameplayTags.InputTag_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.Shift"),
			FString("Key Shift"));
	GameplayTags.InputTag_R_ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.R_ctrl"),
			FString("Key R_ctrl"));
	GameplayTags.InputTag_l_Alt = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.l_Alt"),
			FString("Key l_Alt"));
	GameplayTags.InputTag_R_Alt = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.R_Alt"),
			FString("Key R_Alt"));
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.Passive.1"),
			FString("Passive1")
			);
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Passive.2"),
		FString("Passive2")
		);
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
	* Meta Attributes
	*/
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Meta.IncomingXP"),
			FString("=IncomingXP")
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
	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.None"),
		FString("No Ability - like the nullptr for Ability Tags")
		);
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Summon"),
		FString("Abilities_Summon")
				);
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Attack"),
			FString("Abilities_Attack"));
	GameplayTags.Abilities_Fire_Bullet = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Fire.Bullet"),
			FString("Abilities_Fire_Bullet")
				);
	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Lightning.Electrocute"),
			FString("Electrocute Ability Tag")
			);
	
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.HitReact"),
			FString("Hit React Ability")
			);

	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Eligible"),
		FString("Eligible Status")
		);

	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Equipped"),
		FString("Equipped Status")
		);

	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Locked"),
		FString("Locked Status")
		);

	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Unlocked"),
		FString("Unlocked Status")
		);

	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.None"),
		FString("Type None")
		);

	GameplayTags.Abilities_Type_Active = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Active"),
		FString("Type Active")
		);

	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Passive"),
		FString("Type Passive")
		);

	
	/*
	* Cooldown
	*/
	GameplayTags.Cooldown_Fire_Bullet = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Cooldown.Fire.Bullet"),
				FString("Cooldown_Fire_Bullet"));
	
	/*
	* Combat sockets
	*/

	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("CombatSocket.Weapon"),
			FString("Weapon"));
	GameplayTags.CombatSocket_RightATK = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("CombatSocket.RightATK"),
				FString("Weapon"));
	GameplayTags.CombatSocketLeftATK = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("CombatSocket.LeftATK"),
			FString("Weapon"));

	/*
	* Montage Tags
	*/

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Montage.Attack.1"),
			FString("Attack 1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Montage.Attack.2"),
				FString("Attack 2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Montage.Attack.3"),
			FString("Attack 3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Montage.Attack.4"),
			FString("Attack 4"));
}
