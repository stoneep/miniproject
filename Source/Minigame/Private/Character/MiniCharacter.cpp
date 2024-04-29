// Copyright NexonGames


#include "Character/MiniCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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

// void AMiniCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
//  	
// }
