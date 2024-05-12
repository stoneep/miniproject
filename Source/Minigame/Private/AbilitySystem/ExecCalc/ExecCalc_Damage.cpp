// Copyright NexonGames


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "MiniGameplayTags.h"
#include "AbilitySystem/MiniAttributeSet.h"

struct MiniDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DEF);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Accuracy);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);
	MiniDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, DEF, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Evasion, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Accuracy, Source, false);
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
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

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
	// If Block, halve the damage.
	Damage = bEvasion ? Damage / 2.f : Damage;
	//if (bEvasion) Damage /= 2.f;


	float TargetDEF = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DEFDef, EvaluationParameters, TargetDEF);
	TargetDEF = FMath::Max<float>(TargetDEF, 0.f);
	
	float SourceAccurary = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AccuracyDef, EvaluationParameters, SourceAccurary);
	SourceAccurary = FMath::Max<float>(SourceAccurary, 0.f);

	// Accurary ignores a percentage of  Target's DEF
	const float EffectiveDEF = TargetDEF *= ( 100 - SourceAccurary * 0.25f ) / 100.f;
	// DEF ignores a percentage of incoming Damage
	Damage *= ( 100 - EffectiveDEF * 0.333f ) / 100.f;
	// ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DEFDef, EvaluationParameters, DEF);
	// DEF = FMath::Max<float>(0.f, DEF);
	// ++DEF;

	const FGameplayModifierEvaluatedData EvaluatedData(UMiniAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
