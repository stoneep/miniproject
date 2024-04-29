// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MiniCharacterBase.generated.h"

UCLASS()
class MINIGAME_API AMiniCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	AMiniCharacterBase();

protected:

	virtual void BeginPlay() override;
	
};
