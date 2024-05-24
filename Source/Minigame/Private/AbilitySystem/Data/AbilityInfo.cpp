// Copyright NexonGames


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Minigame/MiniLogChannels.h"

FMiniAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FMiniAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogMini, Error, TEXT("Cant't find info for AbilityTag [%s] OnAbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FMiniAbilityInfo();
}
