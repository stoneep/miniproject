// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MiniWidgetController.h"
#include "SkillMenuWidgetController.generated.h"

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
};
