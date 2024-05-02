// Copyright NexonGames


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMiniAttributeSet* MiniAttributeSet = CastChecked<UMiniAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(MiniAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MiniAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(MiniAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MiniAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMiniAttributeSet* MiniAttributeSet = CastChecked<UMiniAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MiniAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MiniAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MiniAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MiniAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);
	Cast<UMiniAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
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

// void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnHealthChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnMaxHealthChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnManaChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnMaxManaChanged.Broadcast(Data.NewValue);
// }
