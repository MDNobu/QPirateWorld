// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "QAbilityInfo.h"
#include "QGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class QPIRATEWORLD_API UQGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	


public:
	UQGameplayAbilityBase();

	UFUNCTION(BlueprintCallable, Category = "QPirate")
	FQAbilityInfo QueryAbilityInfo();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstance* UIMaterial = nullptr;

};
