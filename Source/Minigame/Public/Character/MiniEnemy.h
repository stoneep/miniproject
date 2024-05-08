// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "Character/MiniCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "MiniEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API AMiniEnemy : public AMiniCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	
	AMiniEnemy();

	virtual int32 GetPlayerLevel() override;
	
protected:
	virtual void BeginPlay() override;

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
