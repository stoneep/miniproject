// Copyright NexonGames


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"

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
	
	if (UMiniAbilitySystemComponent* MiniASC = Cast<UMiniAbilitySystemComponent>(AbilitySystemComponent))
	{
		if(MiniASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(MiniASC);
		}
		else
		{
			MiniASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		MiniASC->EffectAssetTags.AddLambda(
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

void UOverlayWidgetController::OnInitializeStartupAbilities(UMiniAbilitySystemComponent* MiniAbilitySystemComponent)
{
	if(!MiniAbilitySystemComponent->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, MiniAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		FMiniAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(MiniAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = MiniAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	MiniAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}
