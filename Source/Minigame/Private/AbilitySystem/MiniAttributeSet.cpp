// Copyright NexonGames


#include "AbilitySystem/MiniAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "MiniGameplayTags.h"
#include "Interaction/CombatInterface.h"

UMiniAttributeSet::UMiniAttributeSet()
{
	//InitHealth(50.f);
	//InitMaxHealth(100.f);
	//InitMana(10.f);
	//InitMaxMana(50.f);

	const FMiniGameplayTags& GameplayTags = FMiniGameplayTags::Get();
	/*Primary Attributes*/
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_ATK, GetATKAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_DEF, GetDEFAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Accuracy, GetAccuracyAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Stability, GetStabilityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Evasion, GetEvasionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Crit, GetCritAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_CritDMG, GetCritDMGAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Healing, GetHealingAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_NormalAttackRange, GetNormalAttackRangeAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_CrowdControlRES, GetCrowdControlRESAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_CostRecovery, GetCostRecoveryAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_CrowdControlPower, GetCrowdControlPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_RelationshipRank, GetRelationshipRankAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_BonusRecipients, GetBonusRecipientsAttribute);
//4번

	/*Secondary Attributes*/
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_OutdoorCombatPower, GetOutdoorCombatPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_IndoorCombatPower, GetIndoorCombatPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_StreetCombatPower, GetStreetCombatPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
}

void UMiniAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	//
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, StreetCombatPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, OutdoorCombatPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, IndoorCombatPower, COND_None, REPNOTIFY_Always);
	
	//
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, ATK, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, DEF, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Stability, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Accuracy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Evasion, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Crit, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, CritDMG, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Healing, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, NormalAttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, CostRecovery, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, CrowdControlPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, CrowdControlRES, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, RelationshipRank, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, BonusRecipients, COND_None, REPNOTIFY_Always);
	
	//5번
	
	//
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, AP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, EXP, COND_None, REPNOTIFY_Always);
}

void UMiniAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UMiniAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UMiniAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
					CombatInterface->Die();
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FMiniGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
		}
	}
}

void UMiniAttributeSet::OnRep_StreetCombatPower(const FGameplayAttributeData& OldStreetCombatPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, StreetCombatPower, OldStreetCombatPower);
}

void UMiniAttributeSet::OnRep_OutdoorCombatPower(const FGameplayAttributeData& OldOutdoorCombatPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, OutdoorCombatPower, OldOutdoorCombatPower);
}

void UMiniAttributeSet::OnRep_IndoorCombatPower(const FGameplayAttributeData& OldIndoorCombatPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, IndoorCombatPower, OldIndoorCombatPower);
}

void UMiniAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Health, OldHealth);
}

void UMiniAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, MaxHealth, OldMaxHealth);
}

void UMiniAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Mana, OldMana);
}

void UMiniAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, MaxMana, OldMaxMana);
}

void UMiniAttributeSet::OnRep_AP(const FGameplayAttributeData& OldAP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, AP, OldAP);
}

void UMiniAttributeSet::OnRep_EXP(const FGameplayAttributeData& OldEXP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, EXP, OldEXP);
}

void UMiniAttributeSet::OnRep_ATK(const FGameplayAttributeData& OldATK) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, ATK, OldATK);
}

void UMiniAttributeSet::OnRep_DEF(const FGameplayAttributeData& OldDEF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, DEF, OldDEF);
}

void UMiniAttributeSet::OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Accuracy, OldAccuracy);
}

void UMiniAttributeSet::OnRep_Stability(const FGameplayAttributeData& OldStability) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Stability, OldStability);
}

void UMiniAttributeSet::OnRep_Evasion(const FGameplayAttributeData& OldEvasion) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Evasion, OldEvasion);
}

void UMiniAttributeSet::OnRep_Crit(const FGameplayAttributeData& OldCrit) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Crit, OldCrit);
}

void UMiniAttributeSet::OnRep_CritDMG(const FGameplayAttributeData& OldCritDMG) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, CritDMG, OldCritDMG);
}

void UMiniAttributeSet::OnRep_Healing(const FGameplayAttributeData& OldHealing) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Healing, OldHealing);
}

void UMiniAttributeSet::OnRep_NormalAttackRange(const FGameplayAttributeData& OldNormalAttackRange) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, NormalAttackRange, OldNormalAttackRange);
}

void UMiniAttributeSet::OnRep_CrowdControlRES(const FGameplayAttributeData& OldCrowdControlRES) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, CrowdControlRES, OldCrowdControlRES);
}

void UMiniAttributeSet::OnRep_CostRecovery(const FGameplayAttributeData& OldCostRecovery) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, CostRecovery, OldCostRecovery);
}

void UMiniAttributeSet::OnRep_CrowdControlPower(const FGameplayAttributeData& OldCrowdControlPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, CrowdControlPower, OldCrowdControlPower);
}

void UMiniAttributeSet::OnRep_RelationshipRank(const FGameplayAttributeData& OldRelationshipRank) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, RelationshipRank, OldRelationshipRank);
}

void UMiniAttributeSet::OnRep_BonusRecipients(const FGameplayAttributeData& OldBonusRecipients) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, BonusRecipients, OldBonusRecipients);
}
//6번