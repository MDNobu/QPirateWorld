// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "QCharacterBase.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UQAttributeSetBase;
class UQGameplayAbilityBase;

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
	void AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "QPirate")
	void AcquireAbilities(TArray<TSubclassOf<UGameplayAbility>> abilitiesToAcquire);

	UFUNCTION()
	void OnHealthChange(float health, float maxHealth);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChange"))
	void BP_OnHealthChange(float health, float maxHealth);

	UFUNCTION()
	void OnManaChange(float mana, float maxMana);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChange"))
	void BP_OnManaChange(float mana, float maxMana);

	UFUNCTION()
	void OnStrengthChange(float strength, float maxStrength);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStrengthChange"))
	void BP_OnStrengthChange(float strength, float maxStrength);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Die"))
	void BP_Die();

	UFUNCTION(BlueprintCallable, Category = "QPirate")
	bool IsHostile(AQCharacterBase* other) const;

	void AddGameplayTag(const FGameplayTag& tagToAdd);
	void RemoveGameplayTag(const FGameplayTag& tagToRemove);

	/**
	 *  
	 * @param stunDuration <= 0，不会stun，>0 时stun
	 */
	UFUNCTION(BlueprintCallable, Category = "QPirate", meta = (ToolTip = "only stun when duration > 0"))
	void TryStun(float stunDuration);

	UFUNCTION(BlueprintCallable, Category = "QPirate")
	void ApplyGESpecHandelToTargetDataSpecHandle(const FGameplayEffectSpecHandle& geSpecHandle, 
		const FGameplayAbilityTargetDataHandle& gaTargetDataHandle);

#pragma region GetterAndSetters
	const FGameplayTag& GetFullHealthTag() const { return FullHealthTag; }
#pragma endregion

private:
	
	void AutoAssignTeamID();
	void Die();

	void DisableControlInput();
	void EnableControlInput();


	void AddToHUDAbilitySlot(TSubclassOf<UQGameplayAbilityBase> abilityToAdd);
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "QPirate", meta = (AllowPrivateAccess = true))
	UAbilitySystemComponent* AbilitySystemComp = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QPirate", meta = (AllowPrivateAccess = true))
	UQAttributeSetBase* HealthAttribute;

	UPROPERTY( EditAnywhere, Category = "QPirate", meta = (AllowPrivateAccess = true))
	FGameplayTag FullHealthTag;

	bool bIsDead = false;

	const uint8 ENEMY_TEAM_ID = 255;
	const uint8 PLAYER_TEAM_ID = 1;
	/** teamID主要用来决定characterBase对象是否统一阵营，敌对情况 */
	uint8 TeamID = 255;


	FTimerHandle StunTimerHandle;
};
