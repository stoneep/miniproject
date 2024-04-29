// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "Character/MiniCharacterBase.h"
#include "MiniCharacter.generated.h"

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

	UPROPERTY(BlueprintReadOnly)
	EMovementState MovementState;

	UFUNCTION(BlueprintCallable)
	void UpdateMovementState();

// protected:
// 		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
// 	
};
