// Copyright NexonGames

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MiniAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

template<class T>
using TStaticFuncPtr = typename  TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;




/**
 * 
 */
UCLASS()
class MINIGAME_API UMiniAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UMiniAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	/*
	 * Secondary STATUS Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StreetCombatPower, Category = "Secondary Attributes")
	FGameplayAttributeData StreetCombatPower;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, StreetCombatPower);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_OutdoorCombatPower, Category = "Secondary Attributes")
	FGameplayAttributeData OutdoorCombatPower;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, OutdoorCombatPower);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IndoorCombatPower, Category = "Secondary Attributes")
	FGameplayAttributeData IndoorCombatPower;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, IndoorCombatPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, MaxMana);
	
	/*
	 * Primary STATUS Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ATK, Category = "Primary Attributes")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, ATK);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DEF, Category = "Primary Attributes")
	FGameplayAttributeData DEF;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, DEF);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Accuracy, Category = "Primary Attributes")
	FGameplayAttributeData Accuracy;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Accuracy);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Evasion, Category = "Primary Attributes")
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Evasion);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stability, Category = "Primary Attributes")
	FGameplayAttributeData Stability;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Stability);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Crit, Category = "Primary Attributes")
	FGameplayAttributeData Crit;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Crit);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDMG, Category = "Primary Attributes")
	FGameplayAttributeData CritDMG;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, CritDMG);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Healing, Category = "Primary Attributes")
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Healing);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NormalAttackRange, Category = "Primary Attributes")
	FGameplayAttributeData NormalAttackRange;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, NormalAttackRange);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CostRecovery, Category = "Primary Attributes")
	FGameplayAttributeData CostRecovery;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, CostRecovery);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CrowdControlRES, Category = "Primary Attributes")
	FGameplayAttributeData CrowdControlRES;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, CrowdControlRES);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CrowdControlPower, Category = "Primary Attributes")
	FGameplayAttributeData CrowdControlPower;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, CrowdControlPower);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RelationshipRank, Category = "Primary Attributes")
	FGameplayAttributeData RelationshipRank;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, RelationshipRank);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BonusRecipients, Category = "Primary Attributes")
	FGameplayAttributeData BonusRecipients;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, BonusRecipients);
//3번

	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AP, Category = "Vital Attributes")
	FGameplayAttributeData AP;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, AP);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EXP, Category = "Vital Attributes")
	FGameplayAttributeData EXP;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, EXP);

	/*
	* Meta Attributes
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, IncomingDamage);
	
	UFUNCTION()
	void OnRep_StreetCombatPower(const FGameplayAttributeData& OldStreetCombatPower) const;
	UFUNCTION()
	void OnRep_OutdoorCombatPower(const FGameplayAttributeData& OldOutdoorCombatPower) const;
	UFUNCTION()
	void OnRep_IndoorCombatPower(const FGameplayAttributeData& OldIndoorCombatPower) const;
	
	/*
	 * 
	 */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_AP(const FGameplayAttributeData& OldAP) const;
	UFUNCTION()
	void OnRep_EXP(const FGameplayAttributeData& OldEXP) const;
	
	UFUNCTION()
	void OnRep_ATK(const FGameplayAttributeData& OldATK) const;
	UFUNCTION()
	void OnRep_DEF(const FGameplayAttributeData& OldDEF) const;
	UFUNCTION()
	void OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy) const;
	UFUNCTION()
	void OnRep_Stability(const FGameplayAttributeData& OldStability) const;
	UFUNCTION()
	void OnRep_Evasion(const FGameplayAttributeData& OldEvasion) const;
	UFUNCTION()
	void OnRep_Crit(const FGameplayAttributeData& OldCrit) const;
	UFUNCTION()
	void OnRep_CritDMG(const FGameplayAttributeData& OldCritDMG) const;
	UFUNCTION()
	void OnRep_Healing(const FGameplayAttributeData& OldHealing) const;
	UFUNCTION()
	void OnRep_NormalAttackRange(const FGameplayAttributeData& OldNormalAttackRange) const;
	UFUNCTION()
	void OnRep_CrowdControlRES(const FGameplayAttributeData& OldCrowdControlRES) const;
	UFUNCTION()
	void OnRep_CostRecovery(const FGameplayAttributeData& OldCostRecovery) const;
	UFUNCTION()
	void OnRep_CrowdControlPower(const FGameplayAttributeData& OldCrowdControlPower) const;
	UFUNCTION()
	void OnRep_RelationshipRank(const FGameplayAttributeData& OldRelationshipRank) const;
	UFUNCTION()
	void OnRep_BonusRecipients(const FGameplayAttributeData& OldBonusRecipients) const;
	//2번
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
