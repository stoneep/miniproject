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
	GameplayTags.Attributes_Primary_HIT = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.HIT"),
					FString("Hit the target"));
	GameplayTags.Attributes_Primary_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.Dodge"),
					FString("Dodge/Avoid"));
	GameplayTags.Attributes_Primary_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(
					FName("Attributes.Primary.Block"),
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
	
	GameplayTags.Attributes_Secondary_OutdoorCombatPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.OutdoorCombatPower"),
		FString("OutDoorSTR"));
	GameplayTags.Attributes_Secondary_StreetCombatPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.StreetCombatPower"),
		FString("StreetCombatSTR"));
	GameplayTags.Attributes_Secondary_IndoorCombatPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.IndoorCombatPower"),
		FString("IndoorCombatSTR"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("MaxHealth"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("MaxMana"));
}
