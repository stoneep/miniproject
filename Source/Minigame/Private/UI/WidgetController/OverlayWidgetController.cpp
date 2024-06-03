// Copyright NexonGames


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/MiniPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//const UMiniAttributeSet* MiniAttributeSet = CastChecked<UMiniAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(GetMiniAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetMiniAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetMiniAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetMiniAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	GetMiniPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	GetMiniPS()->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel)
		{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMiniAS()->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMiniAS()->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMiniAS()->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetMiniAS()->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);
	
	if (GetMiniASC())
	{
		if(GetMiniASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetMiniASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}
		
		GetMiniASC()->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				
				}
			}
		);
	}
	
	
	
}

// void UOverlayWidgetController::OnInitializeStartupAbilities(UMiniAbilitySystemComponent* MiniAbilitySystemComponent)
// {
// 	if (!MiniAbilitySystemComponent->bStartupAbilitiesGiven) return;
//
// 	FForEachAbility BroadcastDelegate;
// 	BroadcastDelegate.BindLambda([this, MiniAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
// 	{
// 		FMiniAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(MiniAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
// 		Info.InputTag = MiniAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
// 		AbilityInfoDelegate.Broadcast(Info);
// 	});
// 	MiniAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
// }

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	//const AMiniPlayerState* MiniPlayerState = CastChecked<AMiniPlayerState>(PlayerState);
	//const ULevelUpInfo* LevelUpInfo = MiniPlayerState->LevelUpInfo;
	const ULevelUpInfo* LevelUpInfo = GetMiniPS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out MiniPlayerState Blueprint"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
	
}
