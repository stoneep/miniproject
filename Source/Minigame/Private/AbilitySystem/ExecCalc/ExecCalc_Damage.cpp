// Copyright NexonGames


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "MiniGameplayTags.h"
#include "AbilitySystem/MiniAbilitySystemLibrary.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"
#include "MiniAbilityTypes.h"

struct MiniDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DEF);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Accuracy);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Crit);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDMG);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Stability);
	MiniDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, DEF, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Evasion, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Accuracy, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Crit, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, CritDMG, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Stability, Target, false);
	}
};

static const MiniDamageStatics& DamageStatics()
{
	static MiniDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().DEFDef);
	RelevantAttributesToCapture.Add(DamageStatics().EvasionDef);
	RelevantAttributesToCapture.Add(DamageStatics().AccuracyDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDMGDef);
	RelevantAttributesToCapture.Add(DamageStatics().StabilityDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FMiniGameplayTags::Get().Damage);

	
	//float DEF = 0.f;
	float TargetEvasion = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().EvasionDef, EvaluationParameters, TargetEvasion);
	TargetEvasion = FMath::Max<float>(TargetEvasion, 0.f);
	const bool bEvasion = FMath::RandRange(1, 100) < TargetEvasion;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	//FGameplayEffectContext* Context = EffectContextHandle.Get();
	//FMiniGameplayEffectContext* MiniContext = static_cast<FMiniGameplayEffectContext*>(Context);
	//MiniContext->SetIsBlockedHit(bEvasion);
	UMiniAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bEvasion);

	
	// If Block, halve the damage.
	Damage = bEvasion ? Damage / 2.f : Damage;
	//if (bEvasion) Damage /= 2.f;


	float TargetDEF = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DEFDef, EvaluationParameters, TargetDEF);
	TargetDEF = FMath::Max<float>(TargetDEF, 0.f);
	
	float SourceAccuracy = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AccuracyDef, EvaluationParameters, SourceAccuracy);
	SourceAccuracy = FMath::Max<float>(SourceAccuracy, 0.f);

	const UCharacterClassInfo* CharacterClassInfo = UMiniAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* AccuracyCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("Accuracy"), FString());
	const float AccuracyPenetrationCoefficient = AccuracyCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	// Accuracy ignores a percentage of  Target's DEF
	const float Evasion = TargetDEF *= ( 100 - SourceAccuracy * AccuracyPenetrationCoefficient ) / 100.f;

	const FRealCurve* EvasionCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("Evasion"), FString());
	const float EvasionCoefficient = EvasionCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	// DEF ignores a percentage of incoming Damage
	Damage *= ( 100 - Evasion * EvasionCoefficient ) / 100.f;
	
	// ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DEFDef, EvaluationParameters, DEF);
	// DEF = FMath::Max<float>(0.f, DEF);
	// ++DEF;


	float SourceCrit = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDef, EvaluationParameters, SourceCrit);
	SourceCrit = FMath::Max<float>(SourceCrit, 0.f);

	float SourceCritDMG = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDMGDef, EvaluationParameters, SourceCritDMG);
	SourceCritDMG = FMath::Max<float>(SourceCritDMG, 0.f);
	
	float TargetStability = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().StabilityDef, EvaluationParameters, TargetStability);
	TargetStability = FMath::Max<float>(TargetStability, 0.f);

	const FRealCurve* StabilityCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("Stability"), FString());
	const float StabilityCoefficient = StabilityCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	// Critical Hit Resistance reduces Critical percent by a certain percentage
	const float Crit = SourceCrit - TargetStability * StabilityCoefficient;
	const bool bCritDMG = FMath::RandRange(1, 100) < Crit;

	UMiniAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritDMG);
	
	// Bonus Critical DMG
	Damage = bCritDMG ? 2.f * Damage + SourceCritDMG : Damage;

	
	const FGameplayModifierEvaluatedData EvaluatedData(UMiniAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
