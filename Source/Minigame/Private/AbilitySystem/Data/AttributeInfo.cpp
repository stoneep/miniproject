// Copyright NexonGames


#include "AbilitySystem/Data/AttributeInfo.h"

#include "Minigame/MiniLogChannels.h"

FMiniAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FMiniAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogMini, Error, TEXT("Can't find tag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FMiniAttributeInfo();
}
