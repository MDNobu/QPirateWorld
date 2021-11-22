// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QAbilityInfo.generated.h"

class UQGameplayAbilityBase;

UENUM(BlueprintType)
enum class EAbilityCostType : uint8
{
	Health, 
	Mana, 
	Strength
};

USTRUCT(BlueprintType)
struct FQAbilityInfo
{
	GENERATED_BODY()
public:
	FQAbilityInfo();
	FQAbilityInfo(float inCoolDownDuration, float inCost, EAbilityCostType inCostType,
		UMaterialInstance* inUIMaterial, TSubclassOf<UQGameplayAbilityBase> inAbilityClass);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilityInfo")
	float CooldownDuration = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilityInfo")
	float Cost = 20.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilityInfo")
	EAbilityCostType CostType = EAbilityCostType::Mana;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilityInfo")
	UMaterialInstance* UIMaterial = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AbilityInfo")
	TSubclassOf<UQGameplayAbilityBase> AbilityClass;
};