// Copyright NexonGames


#include "AbilitySystem/MiniAbilitySystemLibrary.h"

#include "MiniAbilityTypes.h"
#include "Game/MiniGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "UI/WidgetController/MiniWidgetController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MiniPlayerState.h"
#include "UI/HUD/MiniHUD.h"

bool UMiniAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AMiniHUD*& OutMiniHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutMiniHUD = Cast<AMiniHUD>(PC->GetHUD());
		if (OutMiniHUD)
		{
			AMiniPlayerState* PS = PC->GetPlayerState<AMiniPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWCParams.AttributeSet = AS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.PlayerState = PS;
			OutWCParams.PlayerController = PC;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UMiniAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AMiniHUD* MiniHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, MiniHUD))
	{
		return MiniHUD->GetOverlayWidgetController(WCParams);
	}
	return nullptr;
}

UAttributeMenuWidgetController* UMiniAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AMiniHUD* MiniHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, MiniHUD))
	{
		return MiniHUD->GetAttributeMenuWidgetController(WCParams);
	}
	return nullptr;
}

USkillMenuWidgetController* UMiniAbilitySystemLibrary::GetSkillMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AMiniHUD* MiniHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, MiniHUD))
	{
		return MiniHUD->GetSkillMenuWidgetController(WCParams);
	}
	return nullptr;
}

void UMiniAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UMiniAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

int32 UMiniAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return 0;
	
	const FCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);
	
	return static_cast<int32>(XPReward);
}

UCharacterClassInfo* UMiniAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AMiniGameModeBase* MiniGameMode = Cast<AMiniGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MiniGameMode == nullptr) return nullptr;
	return MiniGameMode->CharacterClassInfo;
}

UAbilityInfo* UMiniAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const AMiniGameModeBase* MiniGameMode = Cast<AMiniGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MiniGameMode == nullptr) return nullptr;
	return MiniGameMode->AbilityInfo;
}

bool UMiniAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMiniGameplayEffectContext* MiniEffectContext = static_cast<const FMiniGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MiniEffectContext->IsBlockedHit();
	}
	return false;
}

bool UMiniAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMiniGameplayEffectContext* MiniEffectContext = static_cast<const FMiniGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MiniEffectContext->IsCriticalHit();
	}
	return false;
}

void UMiniAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FMiniGameplayEffectContext* MiniEffectContext = static_cast<FMiniGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MiniEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UMiniAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FMiniGameplayEffectContext* MiniEffectContext = static_cast<FMiniGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MiniEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UMiniAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
	const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

bool UMiniAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;
	return !bFriends;
}


