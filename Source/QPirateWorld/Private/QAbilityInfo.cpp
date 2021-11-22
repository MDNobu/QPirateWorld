// Fill out your copyright notice in the Description page of Project Settings.


#include "QAbilityInfo.h"


FQAbilityInfo::FQAbilityInfo()
{

}

FQAbilityInfo::FQAbilityInfo(
	float inCoolDownDuration, float inCost, 
	EAbilityCostType inCostType, UMaterialInstance* inUIMaterial, 
	TSubclassOf<UQGameplayAbilityBase> inAbilityClass) : CooldownDuration(inCoolDownDuration), 
	Cost(inCost), CostType(inCostType), UIMaterial(inUIMaterial), AbilityClass(inAbilityClass)
{

}
