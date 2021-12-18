// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "QAttributeSetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, health, float, maxHealth);

/**
 * 
 */
UCLASS()
class QPIRATEWORLD_API UQAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	UQAttributeSetBase();

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate")
	FGameplayAttributeData Health {200.0f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate")
	FGameplayAttributeData MaxHealth {200.0f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate")
	FGameplayAttributeData Mana {100.0f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate")
	FGameplayAttributeData MaxMana {100.0f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate")
	FGameplayAttributeData Strength {100.0f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate")
	FGameplayAttributeData MaxStrength {100.0f};

	FOnHealthChangeDelegate OnHealthChange;
	FOnHealthChangeDelegate OnManaChange;
	FOnHealthChangeDelegate OnStrengthChange;

};
