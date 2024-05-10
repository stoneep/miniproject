// Copyright NexonGames


#include "Character/MiniEnemy.h"

#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Minigame/Minigame.h"
#include "UI/Widget/MiniUserWidget.h"

AMiniEnemy::AMiniEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UMiniAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UMiniAttributeSet>("AttributeSet");
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

int32 AMiniEnemy::GetPlayerLevel()
{
	return Level;
}

void AMiniEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
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
		OnHealthChanged.Broadcast(MiniAS->GetHealth());
		OnMaxHealthChanged.Broadcast(MiniAS->GetMaxHealth());
	}
}

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
