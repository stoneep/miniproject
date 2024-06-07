// Copyright NexonGames


#include "AbilitySystem/Abilities/MiniGameplayAbility.h"

FString UMiniGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - None None None None None None None None None None ", Level);
}

FString UMiniGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Next Level: </><Level>%d</> \n<Default>Much more damage. </>"), Level);
}

FString UMiniGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Skill Locked Until Level: %d</>"), Level);
}
