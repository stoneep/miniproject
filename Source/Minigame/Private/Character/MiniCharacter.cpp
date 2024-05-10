// Copyright NexonGames


#include "Character/MiniCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
//#include "AbilitySystem/MiniAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "Player/MiniPlayerController.h"
#include "Player/MiniPlayerState.h"
#include "UI/HUD/MiniHUD.h"
#include "UI/Widget/MiniUserWidget.h"

AMiniCharacter::AMiniCharacter()
 {
 	GetCharacterMovement()->bOrientRotationToMovement = true;
 	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f);
 	GetCharacterMovement()->bConstrainToPlane = true;
 	GetCharacterMovement()->bSnapToPlaneAtStart = true;
 	
 	bUseControllerRotationPitch = false;
 	bUseControllerRotationRoll = false;
 	bUseControllerRotationYaw = false;

 	MovementState = EMovementState::Idle;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
 }

void AMiniCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AMiniCharacter::UpdateMovementState()
{
 	if (GetVelocity().SizeSquared() > 0.f)
 	{
 		MovementState = EMovementState::Moving;
 	}
    else
    {
	    MovementState = EMovementState::Idle;
    }
 	
}


void AMiniCharacter::OnRep_PlayerState()
{
 	Super::OnRep_PlayerState();

 	// Init ability actor info for the Client
 	InitAbilityActorInfo();
}

int32 AMiniCharacter::GetPlayerLevel()
{
	const AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
	check(MiniPlayerState);
	return MiniPlayerState->GetPlayerLevel();
}

void AMiniCharacter::InitAbilityActorInfo()
{
 	AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
 	check(MiniPlayerState);
 	MiniPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MiniPlayerState, this);
	Cast<UMiniAbilitySystemComponent>(MiniPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
 	AbilitySystemComponent = MiniPlayerState->GetAbilitySystemComponent();
 	AttributeSet = MiniPlayerState->GetAttributeSet();

	if (AMiniPlayerController* MiniPlayerController = Cast<AMiniPlayerController>(GetController()))
	{
		if (AMiniHUD* MiniHUD = Cast<AMiniHUD>(MiniPlayerController->GetHUD()))
		{
			MiniHUD->InitOverlay(MiniPlayerController, MiniPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}

void AMiniCharacter::BeginPlay()
{
	Super::BeginPlay();

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

