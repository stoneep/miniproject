// Copyright NexonGames


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MiniAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMiniAttributeSet* MiniAttributeSet = CastChecked<UMiniAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(MiniAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MiniAttributeSet->GetMaxHealth());
}
