// Copyright NexonGames


#include "Character/MiniCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MiniPlayerState.h"
#include "UI/Widget/MiniUserWidget.h"

AMiniCharacter::AMiniCharacter()
 {
 	GetCharacterMovement()->bOrientRotationToMovement = false;
 	//GetCharacterMovement()->RotationRate = FRotatpr;
 	GetCharacterMovement()->bConstrainToPlane = true;
 	GetCharacterMovement()->bSnapToPlaneAtStart = true;
 	
 	bUseControllerRotationPitch = false;
 	bUseControllerRotationRoll = false;
 	bUseControllerRotationYaw = false;

 	MovementState = EMovementState::Idle;

	Healthbar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	Healthbar->SetupAttachment(GetRootComponent());

	if(UMiniUserWidget* MiniUserWidget = Cast<UMiniUserWidget>(Healthbar->GetUserWidgetObject()))
	{
		MiniUserWidget->SetWidgetController(this);
	}
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

void AMiniCharacter::PossessedBy(AController* NewController)
{
 	Super::PossessedBy(NewController);

 	// Init ability actor info for the Server
 	InitAbilityActorInfo();
}

void AMiniCharacter::OnRep_PlayerState()
{
 	Super::OnRep_PlayerState();

 	// Init ability actor info for the Client
 	InitAbilityActorInfo();
}

void AMiniCharacter::InitAbilityActorInfo()
{
 	AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
 	check(MiniPlayerState);
 	MiniPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MiniPlayerState, this);
 	AbilitySystemComponent = MiniPlayerState->GetAbilitySystemComponent();
 	AttributeSet = MiniPlayerState->GetAttributeSet();

	
}

