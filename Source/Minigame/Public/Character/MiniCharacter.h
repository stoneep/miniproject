// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "Character/MiniCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "MiniCharacter.generated.h"

class UWidgetComponent;

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle,
	Moving
};

/**
 * 
 */
UCLASS()
class MINIGAME_API AMiniCharacter : public AMiniCharacterBase
{
	GENERATED_BODY()

public:

	AMiniCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual int32 GetPlayerLevel() override;
	
	UPROPERTY(BlueprintReadOnly)
	EMovementState MovementState;

	UFUNCTION(BlueprintCallable)
	void UpdateMovementState();

private:
	virtual void InitAbilityActorInfo() override;

 protected:
 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
 	TObjectPtr<UWidgetComponent> Healthbar;
};
