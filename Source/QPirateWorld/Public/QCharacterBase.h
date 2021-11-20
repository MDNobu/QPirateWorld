// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "QCharacterBase.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UQAttributeSetBase;

UCLASS()
class QPIRATEWORLD_API AQCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "QPirate")
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnHealthChange(float health, float maxHealth);
private:
	UFUNCTION()
	void OnHealthChange(float health, float maxHealth);

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "QPirate", meta = (AllowPrivateAccess = true))
	UAbilitySystemComponent* AbilitySystemComp = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate", meta = (AllowPrivateAccess = true))
	UQAttributeSetBase* HealthAttribute;


};
