// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "QGATargetActorGroundBlast.generated.h"

class UDecalComponent;

/**
 * 
 */
UCLASS()
class QPIRATEWORLD_API AQGATargetActorGroundBlast : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	AQGATargetActorGroundBlast();

	void StartTargeting(UGameplayAbility* Ability) override;

	void ConfirmTargetingAndContinue() override;

	UFUNCTION(BlueprintCallable, Category = "QShooter")
	bool GetLookAtPoint(FVector& outLookAtLocation);

	/** radius of the groundBlast circle */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QShooter", meta = (ExposeOnSpawn = true))
	float Radius = 200.0f;

	void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "QPirate")
	UDecalComponent* DecalComp = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "QPirate")
	USceneComponent* RootComp = nullptr;
};
