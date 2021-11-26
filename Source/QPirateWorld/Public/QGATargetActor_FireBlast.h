// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "QGATargetActor_FireBlast.generated.h"

/**
 * 
 */
UCLASS()
class QPIRATEWORLD_API AQGATargetActor_FireBlast : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:


	void StartTargeting(UGameplayAbility* Ability) override;


	void ConfirmTargetingAndContinue() override;

	/** radius of the fireblast circle */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QShooter", meta = (ExposeOnSpawn = true))
	float Radius = 200.0f;

};
