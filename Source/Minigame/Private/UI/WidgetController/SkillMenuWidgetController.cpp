// Copyright NexonGames


#include "UI/WidgetController/SkillMenuWidgetController.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/MiniPlayerState.h"

void USkillMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	SkillPointsChanged.Broadcast(GetMiniPS()->GetSkillPoints());
}

void USkillMenuWidgetController::BindCallbacksToDependencies()
{
	GetMiniASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
	{
		if (AbilityInfo)
		{
			FMiniAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	}
	);
	GetMiniPS()->OnSkillPointsChangedDelegate.AddLambda([this](int32 SpellPoints){SkillPointsChanged.Broadcast(SpellPoints);});
}
