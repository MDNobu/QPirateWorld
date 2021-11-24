// Fill out your copyright notice in the Description page of Project Settings.


#include "QGameplayAbilityBase.h"
#include "GameplayEffect.h"

UQGameplayAbilityBase::UQGameplayAbilityBase()
{

}

FQAbilityInfo UQGameplayAbilityBase::QueryAbilityInfo()
{
	FQAbilityInfo resAbilityInfo;
	resAbilityInfo.UIMaterial = UIMaterial;
	resAbilityInfo.AbilityClass = GetClass();

	UGameplayEffect* cooldownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* costEffect = GetCostGameplayEffect();

	if (cooldownEffect)
	{
		float cooldownDuration = 0.0f;
		cooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1.0f, cooldownDuration);

		resAbilityInfo.CooldownDuration = cooldownDuration;
	}

	if (costEffect && 
		(costEffect->Modifiers.Num() > 0))
	{
		float cost = 0.0f;
		EAbilityCostType costType = EAbilityCostType::Mana;

		FGameplayModifierInfo modifierInfo = costEffect->Modifiers[0];
		modifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1.0f, cost);

		FGameplayAttribute modifyAttribut = modifierInfo.Attribute;
		FString costAttributeName = modifyAttribut.AttributeName;

		if (costAttributeName.Equals(TEXT("Health")))
		{
			costType = EAbilityCostType::Health;
		} else if (costAttributeName.Equals(TEXT("Mana")) )
		{
			costType = EAbilityCostType::Mana;
		} else if (costAttributeName.Equals(TEXT("Strength")) )
		{
			costType = EAbilityCostType::Strength;
		}

		resAbilityInfo.Cost = cost;
		resAbilityInfo.CostType = costType;
	}

	return resAbilityInfo;
}
