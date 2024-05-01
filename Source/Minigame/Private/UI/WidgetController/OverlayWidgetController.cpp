// Copyright NexonGames


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MiniAttributeSet.h"

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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MiniAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MiniAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MiniAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		MiniAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
