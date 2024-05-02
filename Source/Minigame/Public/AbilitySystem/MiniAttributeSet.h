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

	/*
	 * Primary Attributes
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
	 * Vital STATUS Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ATK, Category = "Primary Attributes")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, ATK);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DEF, Category = "Primary Attributes")
	FGameplayAttributeData DEF;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, DEF);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HIT, Category = "Primary Attributes")
	FGameplayAttributeData HIT;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, HIT);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dodge, Category = "Primary Attributes")
	FGameplayAttributeData Dodge;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Dodge);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Block, Category = "Primary Attributes")
	FGameplayAttributeData Block;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Block);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Crit, Category = "Primary Attributes")
	FGameplayAttributeData Crit;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Crit);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDMG, Category = "Primary Attributes")
	FGameplayAttributeData CritDMG;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, CritDMG);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Healing, Category = "Primary Attributes")
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UMiniAttributeSet, Healing);

//
	
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
	void OnRep_HIT(const FGameplayAttributeData& OldHIT) const;
	UFUNCTION()
	void OnRep_Dodge(const FGameplayAttributeData& OldDodge) const;
	UFUNCTION()
	void OnRep_Block(const FGameplayAttributeData& OldBlock) const;
	UFUNCTION()
	void OnRep_Crit(const FGameplayAttributeData& OldCrit) const;
	UFUNCTION()
	void OnRep_CritDMG(const FGameplayAttributeData& OldCritDMG) const;
	UFUNCTION()
	void OnRep_Healing(const FGameplayAttributeData& OldHealing) const;
	
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
