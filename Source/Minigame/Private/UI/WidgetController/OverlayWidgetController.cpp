// Copyright NexonGames


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/MiniPlayerState.h"

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
	AMiniPlayerState* MiniPlayerState = CastChecked<AMiniPlayerState>(PlayerState);
	MiniPlayerState->OnLevelChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	MiniPlayerState->OnLevelChangedDelegate.AddLambda([this](int32 NewLevel){OnPlayerLevelChangedDelegate.Broadcast(NewLevel);});
	
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

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	AMiniPlayerState* MiniPlayerState = CastChecked<AMiniPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = MiniPlayerState->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

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
