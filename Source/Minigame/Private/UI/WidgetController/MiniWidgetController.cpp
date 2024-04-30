// Copyright NexonGames


#include "UI/WidgetController/MiniWidgetController.h"

void UMiniWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UMiniWidgetController::BroadcastInitialValues()
{
}
