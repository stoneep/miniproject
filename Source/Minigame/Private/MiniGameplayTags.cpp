// Copyright NexonGames


#include "MiniGameplayTags.h"
#include "GameplayTagsManager.h"

FMiniGameplayTags FMiniGameplayTags::GameplayTags;

void FMiniGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_StreetCombatPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Outdoor"), FString("OutDoorSTRSetting"));
}
