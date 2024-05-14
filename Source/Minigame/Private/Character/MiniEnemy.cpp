// Copyright NexonGames


#include "Character/MiniEnemy.h"

#include "MiniGameplayTags.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAbilitySystemLibrary.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AI/MiniAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Minigame/Minigame.h"
#include "UI/Widget/MiniUserWidget.h"

AMiniEnemy::AMiniEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UMiniAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	AttributeSet = CreateDefaultSubobject<UMiniAttributeSet>("AttributeSet");
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AMiniEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	MiniAIController = Cast<AMiniAIController>(NewController);
	MiniAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	MiniAIController->RunBehaviorTree(BehaviorTree);
	MiniAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	MiniAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dealer"), CharacterClass != ECharacterClass::Tank);
}

int32 AMiniEnemy::GetPlayerLevel()
{
	return Level;
}

void AMiniEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AMiniEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UMiniAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}
	if (UMiniUserWidget* MiniUserWidget = Cast<UMiniUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		MiniUserWidget->SetWidgetController(this);
	}

	if (const UMiniAttributeSet* MiniAS = Cast<UMiniAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MiniAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MiniAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->RegisterGameplayTagEvent(FMiniGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AMiniEnemy::HitReactTagChanged
		);
		// AbilitySystemComponent->RegisterGameplayTagEvent(FMiniGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		// 	this,
		// 	&AMiniEnemy::DieReactTagChanged
		// );
		
		OnHealthChanged.Broadcast(MiniAS->GetHealth());
		OnMaxHealthChanged.Broadcast(MiniAS->GetMaxHealth());
	}
}

void AMiniEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	MiniAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
}

// void AMiniEnemy::DieReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
// {
// 	bDieReacting = NewCount > 0;
// }

void AMiniEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AMiniEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void AMiniEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMiniAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}

void AMiniEnemy::InitializeDefaultAttributes() const
{
	UMiniAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
