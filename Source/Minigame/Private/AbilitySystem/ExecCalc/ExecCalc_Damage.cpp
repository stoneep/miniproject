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

//
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BulletResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	MiniDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, DEF, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Evasion, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Accuracy, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Crit, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, CritDMG, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, Stability, Target, false);

		//
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, BulletResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniAttributeSet, PhysicalResistance, Target, false);

		const FMiniGameplayTags& Tags = FMiniGameplayTags::Get();

		TagsToCaptureDefs.Add(Tags.Attributes_Primary_DEF, DEFDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Evasion, EvasionDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Accuracy, AccuracyDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Crit, CritDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_CritDMG, CritDMGDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Stability, StabilityDef);
		
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Bullet, BulletResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, ArcaneResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
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
	
	RelevantAttributesToCapture.Add(DamageStatics().BulletResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1.f;
	if(SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1.f;
	if(TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}
	// ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	// ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	// for (FGameplayTag DamageTypeTag : FMiniGameplayTags::Get().DamageTypes)
	// {
	// 	const float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag);
	// 	Damage += DamageTypeValue;
	// }
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair  : FMiniGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(MiniDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = MiniDamageStatics().TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance ) / 100.f;

		Damage += DamageTypeValue;
	}
	
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
	const float AccuracyPenetrationCoefficient = AccuracyCurve->Eval(SourcePlayerLevel);
	
	// Accuracy ignores a percentage of  Target's DEF
	const float Evasion = TargetDEF *= ( 100 - SourceAccuracy * AccuracyPenetrationCoefficient ) / 100.f;

	const FRealCurve* EvasionCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("Evasion"), FString());
	const float EvasionCoefficient = EvasionCurve->Eval(TargetPlayerLevel);
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
	const float StabilityCoefficient = StabilityCurve->Eval(TargetPlayerLevel);
	
	// Critical Hit Resistance reduces Critical percent by a certain percentage
	const float Crit = SourceCrit - TargetStability * StabilityCoefficient;
	const bool bCritDMG = FMath::RandRange(1, 100) < Crit;

	UMiniAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritDMG);
	
	// Bonus Critical DMG
	Damage = bCritDMG ? 2.f * Damage + SourceCritDMG : Damage;

	
	const FGameplayModifierEvaluatedData EvaluatedData(UMiniAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
