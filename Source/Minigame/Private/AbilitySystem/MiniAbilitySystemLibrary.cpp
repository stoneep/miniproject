// Copyright NexonGames


#include "AbilitySystem/MiniAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MiniPlayerState.h"
#include "UI/HUD/MiniHUD.h"

UOverlayWidgetController* UMiniAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMiniHUD* MiniHUD = Cast<AMiniHUD>(PC->GetHUD()))
		{
			AMiniPlayerState* PS = PC->GetPlayerState<AMiniPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return MiniHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UMiniAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMiniHUD* MiniHUD = Cast<AMiniHUD>(PC->GetHUD()))
		{
			AMiniPlayerState* PS = PC->GetPlayerState<AMiniPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return MiniHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
