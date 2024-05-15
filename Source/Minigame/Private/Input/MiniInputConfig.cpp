// Copyright NexonGames


#include "Input/MiniInputConfig.h"

const UInputAction* UMiniInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FMiniInputAction& Action: AbilityInputActions)
	{
		if(Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	
	return nullptr;
}
