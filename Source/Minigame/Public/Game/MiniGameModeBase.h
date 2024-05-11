// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class MINIGAME_API AMiniGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
