// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "MiniGameplayTags.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/MiniWidgetController.h"
#include "SkillMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSkillSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled, FString, DescriptionString, FString, NextLevelDescriptionString);

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MINIGAME_API USkillMenuWidgetController : public UMiniWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SkillPointsChanged;

	UPROPERTY(BlueprintAssignable)
	FSkillSelectedSignature SkillSelectedDelegate;

	UFUNCTION(BlueprintCallable)
	void SkillSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();
	
private:
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SkillPoints, bool& bShouldEnableSkillPointsButton, bool& bShouldEnableEquipButton);

	FSelectedAbility SelectedAbility = { FMiniGameplayTags::Get().Abilities_None,  FMiniGameplayTags::Get().Abilities_Status_Locked };
	int32 CurrentSkillPoints = 0;
};
