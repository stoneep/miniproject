// Copyright NexonGames


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "MiniGameplayTags.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/MiniPlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UMiniAttributeSet* AS = CastChecked<UMiniAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
	AMiniPlayerState* MiniPlayerState = CastChecked<AMiniPlayerState>(PlayerState);
	MiniPlayerState->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			AttributePointsChangedDelegate.Broadcast(Points);
		}
	);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UMiniAttributeSet* AS = CastChecked<UMiniAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());

		AMiniPlayerState* MiniPlayerState = CastChecked<AMiniPlayerState>(PlayerState);
		AttributePointsChangedDelegate.Broadcast(MiniPlayerState->GetAttributePoints());
	}
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UMiniAbilitySystemComponent* MiniASC = CastChecked<UMiniAbilitySystemComponent>(AbilitySystemComponent);
	MiniASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                            const FGameplayAttribute& Attribute) const
{
	FMiniAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
