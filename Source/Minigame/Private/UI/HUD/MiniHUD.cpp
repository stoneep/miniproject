// Copyright NexonGames


#include "UI/HUD/MiniHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/Widget/MiniUserWidget.h"
#include "UI/WidgetController/SkillMenuWidgetController.h"

UOverlayWidgetController* AMiniHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AMiniHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if(AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

USkillMenuWidgetController* AMiniHUD::GetSkillMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (SkillMenuWidgetController == nullptr)
	{
		SkillMenuWidgetController = NewObject<USkillMenuWidgetController>(this, SkillMenuWidgetControllerClass);
		SkillMenuWidgetController->SetWidgetControllerParams(WCParams);
		SkillMenuWidgetController->BindCallbacksToDependencies();
	}
	return SkillMenuWidgetController;
}

void AMiniHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay uninitialized"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay uninitialized"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UMiniUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}
