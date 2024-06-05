// Copyright NexonGames


#include "UI/WidgetController/MiniWidgetController.h"

#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/MiniPlayerController.h"
#include "Player/MiniPlayerState.h"

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

void UMiniWidgetController::BindCallbacksToDependencies()
{
}

void UMiniWidgetController::BroadcastAbilityInfo()
{
	if (!GetMiniASC()->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FMiniAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(MiniAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = MiniAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = MiniAbilitySystemComponent->GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	GetMiniASC()->ForEachAbility(BroadcastDelegate);
}

AMiniPlayerController* UMiniWidgetController::GetMiniPC()
{
	if (MiniPlayerController == nullptr)
	{
		MiniPlayerController = Cast<AMiniPlayerController>(PlayerController);
	}
	return MiniPlayerController;
}

AMiniPlayerState* UMiniWidgetController::GetMiniPS()
{
	if (MiniPlayerState == nullptr)
	{
		MiniPlayerState = Cast<AMiniPlayerState>(PlayerState);
	}
	return MiniPlayerState;
}

UMiniAbilitySystemComponent* UMiniWidgetController::GetMiniASC()
{
	if (MiniAbilitySystemComponent == nullptr)
	{
		MiniAbilitySystemComponent = Cast<UMiniAbilitySystemComponent>(AbilitySystemComponent);
	}
	return MiniAbilitySystemComponent;
}

UMiniAttributeSet* UMiniWidgetController::GetMiniAS()
{
	if (MiniAttributeSet == nullptr)
	{
		MiniAttributeSet = Cast<UMiniAttributeSet>(AttributeSet);
	}
	return MiniAttributeSet;
}
