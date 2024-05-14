// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MiniAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class MINIGAME_API AMiniAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMiniAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

};
