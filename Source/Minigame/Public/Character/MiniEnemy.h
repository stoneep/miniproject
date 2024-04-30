// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "Character/MiniCharacterBase.h"
#include "MiniEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API AMiniEnemy : public AMiniCharacterBase
{
	GENERATED_BODY()

	AMiniEnemy();

protected:
	virtual void BeginPlay() override;
};
