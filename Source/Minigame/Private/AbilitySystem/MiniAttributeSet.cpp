// Copyright NexonGames


#include "AbilitySystem/MiniAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "MiniGameplayTags.h"

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
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_HIT, GetHITAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Dodge, GetDodgeAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Block, GetBlockAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Crit, GetCritAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_CritDMG, GetCritDMGAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Healing, GetHealingAttribute);


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
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Dodge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, HIT, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Block, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Crit, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, CritDMG, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMiniAttributeSet, Healing, COND_None, REPNOTIFY_Always);
	
	
	
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
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
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

void UMiniAttributeSet::OnRep_HIT(const FGameplayAttributeData& OldHIT) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, HIT, OldHIT);
}

void UMiniAttributeSet::OnRep_Dodge(const FGameplayAttributeData& OldDodge) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Dodge, OldDodge);
}

void UMiniAttributeSet::OnRep_Block(const FGameplayAttributeData& OldBlock) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMiniAttributeSet, Block, OldBlock);
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

