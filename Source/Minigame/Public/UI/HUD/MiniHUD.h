// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/MiniUserWidget.h"
#include "UI/WidgetController/MiniWidgetController.h"
#include "MiniHUD.generated.h"

class UMiniUserWidget;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UMiniUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class MINIGAME_API AMiniHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UMiniUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMiniUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
