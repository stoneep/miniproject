// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "Character/MiniCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Interaction/PlayerInterface.h"
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
class MINIGAME_API AMiniCharacter : public AMiniCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:

	AMiniCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	virtual int32 GetSkillPointsReward_Implementation(int32 Level) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSkillPoints_Implementation(int32 InSkillPoints) override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintReadOnly)
	EMovementState MovementState;

	UFUNCTION(BlueprintCallable)
	void UpdateMovementState();

private:
	virtual void InitAbilityActorInfo() override;

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
