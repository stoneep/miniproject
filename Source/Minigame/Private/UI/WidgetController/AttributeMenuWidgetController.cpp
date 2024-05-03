// Copyright NexonGames


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "MiniGameplayTags.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UMiniAttributeSet* AS = CastChecked<UMiniAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FMiniAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}
