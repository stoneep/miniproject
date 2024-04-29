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
 }
