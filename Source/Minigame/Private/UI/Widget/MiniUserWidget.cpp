// Copyright NexonGames


#include "UI/Widget/MiniUserWidget.h"

void UMiniUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
