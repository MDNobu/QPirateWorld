// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QAbilityInfo.h"
#include "GameFramework/PlayerController.h"
#include "QPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class QPIRATEWORLD_API AQPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "QPirate")
	void AddToHUDAbilitySlot(FQAbilityInfo abilityInfo);
};
