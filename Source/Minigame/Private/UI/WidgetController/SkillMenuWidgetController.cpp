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
		if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;
			bool bEnableSpendPoints = false;
			bool bEnableEquip = false;
			ShouldEnableButtons(StatusTag, CurrentSkillPoints, bEnableSpendPoints, bEnableEquip);
			SkillSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);
		}
		if (AbilityInfo)
		{
			FMiniAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	}
	);
	GetMiniPS()->OnSkillPointsChangedDelegate.AddLambda([this](int32 SkillPoints)
	{
		SkillPointsChanged.Broadcast(SkillPoints);
		CurrentSkillPoints = SkillPoints;

		bool bEnableSpendPoints = false;
		bool bEnableEquip = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSkillPoints, bEnableSpendPoints, bEnableEquip);
		SkillSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);
	}
	);
}

void USkillMenuWidgetController::SkillSelected(const FGameplayTag& AbilityTag)
{
	const FMiniGameplayTags GameplayTags = FMiniGameplayTags::Get();	
	const int32 SkillPoints = GetMiniPS()->GetSkillPoints();
	FGameplayTag AbilityStatus;	

	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const FGameplayAbilitySpec* AbilitySpec = GetMiniASC()->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec != nullptr;
	if (!bTagValid || bTagNone || !bSpecValid)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetMiniASC()->GetStatusFromSpec(*AbilitySpec);
	}
	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	bool bEnableSpendPoints = false;
	bool bEnableEquip = false;
	ShouldEnableButtons(AbilityStatus, SkillPoints, bEnableSpendPoints, bEnableEquip);
	SkillSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);
}

void USkillMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SkillPoints,
	bool& bShouldEnableSkillPointsButton, bool& bShouldEnableEquipButton)
{
	const FMiniGameplayTags GameplayTags = FMiniGameplayTags::Get();

	bShouldEnableSkillPointsButton = false;
	bShouldEnableEquipButton = false;
	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButton = true;
		if (SkillPoints > 0)
		{
			bShouldEnableSkillPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SkillPoints > 0)
		{
			bShouldEnableSkillPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		if (SkillPoints > 0)
		{
			bShouldEnableSkillPointsButton = true;
		}
	}
}
