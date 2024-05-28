// Copyright NexonGames


#include "Character/MiniCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/MiniPlayerController.h"
#include "Player/MiniPlayerState.h"
#include "UI/HUD/MiniHUD.h"
#include "NiagaraComponent.h"
// #include "Camera/CameraComponent.h"
// #include "GameFramework/SpringArmComponent.h"
#include "UI/Widget/MiniUserWidget.h"

AMiniCharacter::AMiniCharacter()
 {
	// CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	// CameraBoom->SetupAttachment(GetRootComponent());
	// CameraBoom->SetUsingAbsoluteRotation(true);
	// CameraBoom->bDoCollisionTest = false;
	// //
	// TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	// TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// TopDownCameraComponent->bUsePawnControlRotation = false;

	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;
	
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

	CharacterClass = ECharacterClass::Elementalist;
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

void AMiniCharacter::AddToXP_Implementation(int32 InXP)
{
	AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
	check(MiniPlayerState);
	MiniPlayerState->AddToXP(InXP);
}

void AMiniCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

void AMiniCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		// const FVector CameraLocation = TopDownCameraComponent->GetComponentLocation();
		// const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
		// const FRotator ToCameraRotation = (CameraLocation - NiagaraSystemLocation).Rotation();
		// LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 AMiniCharacter::GetXP_Implementation() const
{
	const AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
	check(MiniPlayerState);
	return MiniPlayerState->GetXP();
}

int32 AMiniCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
	check(MiniPlayerState);
	return MiniPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AMiniCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
	check(MiniPlayerState);
	return MiniPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
}

int32 AMiniCharacter::GetSkillPointsReward_Implementation(int32 Level) const
{
	const AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
	check(MiniPlayerState);
	return MiniPlayerState->LevelUpInfo->LevelUpInformation[Level].SkillPointAward;
}

void AMiniCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AMiniPlayerState* MiniPlayerState = GetPlayerState<AMiniPlayerState>();
	check(MiniPlayerState);
	MiniPlayerState->AddToLevel(InPlayerLevel);
}

void AMiniCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	//
}

void AMiniCharacter::AddToSkillPoints_Implementation(int32 InSkillPoints)
{
	//
}

int32 AMiniCharacter::GetPlayerLevel_Implementation()
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

