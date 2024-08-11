// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MiniProjectileSkill.h"
#include "MiniBullet.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniBullet : public UMiniProjectileSkill
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

};
