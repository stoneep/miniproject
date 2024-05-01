// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MiniWidgetController.h"
#include "AbilitySystemComponent.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MINIGAME_API UOverlayWidgetController : public UMiniWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	UPROPERTY(BlueprintAssignable, Category="Mini|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="Mini|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="Mini|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category="Mini|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	
};

