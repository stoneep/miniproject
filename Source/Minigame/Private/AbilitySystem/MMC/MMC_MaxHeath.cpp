// Copyright NexonGames


#include "AbilitySystem/MMC/MMC_MaxHeath.h"

#include "AbilitySystem/MiniAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHeath::UMMC_MaxHeath()
{
	EXPDef.AttributeToCapture = UMiniAttributeSet::GetEXPAttribute();
	EXPDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	EXPDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(EXPDef);
}

float UMMC_MaxHeath::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float EXP = 0.f;
	GetCapturedAttributeMagnitude(EXPDef, Spec, EvaluationParameters, EXP);
	EXP = FMath::Max<float>(EXP, 0.f);

	int32 PlayerLevel = 1;
	if(Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}
	return 80.f + 2.5f * EXP + 10.f *PlayerLevel;
}
