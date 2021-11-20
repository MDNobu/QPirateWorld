// Fill out your copyright notice in the Description page of Project Settings.


#include "QCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "QAttributeSetBase.h"
#include "AIController.h"
#include "BrainComponent.h"

// Sets default values
AQCharacterBase::AQCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));

	HealthAttribute = CreateDefaultSubobject<UQAttributeSetBase>(TEXT("HealthAttribute"));
}

// Called when the game starts or when spawned
void AQCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	HealthAttribute->OnHealthChange.AddDynamic(this, &AQCharacterBase::OnHealthChange);
	HealthAttribute->OnManaChange.AddDynamic(this, &AQCharacterBase::OnManaChange);
	HealthAttribute->OnStrengthChange.AddDynamic(this, &AQCharacterBase::OnStrengthChange);

	AutoAssignTeamID();
}

// Called every frame
void AQCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AQCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AQCharacterBase::AquireAbility(TSubclassOf<UGameplayAbility> abilityToAquire)
{
	if (AbilitySystemComp)
	{
		if (HasAuthority() && abilityToAquire)
		{
			const FGameplayAbilitySpec abilitySpec(abilityToAquire, 1) ;
			//abilitySpec.
			AbilitySystemComp->GiveAbility(abilitySpec);
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}


bool AQCharacterBase::IsHostile(AQCharacterBase* other) const
{
	bool bHostile = false;
	bHostile = other && (other->TeamID != this->TeamID);
	return bHostile;
}

void AQCharacterBase::OnHealthChange(float health, float maxHealth)
{
	if (health <= 0 && !bIsDead)
	{
		bIsDead = true;
		Die();
		BP_Die();
	}

	BP_OnHealthChange(health, maxHealth);
}

void AQCharacterBase::OnManaChange(float mana, float maxMana)
{
	BP_OnManaChange(mana, maxMana);
}

void AQCharacterBase::OnStrengthChange(float strength, float maxStrength)
{
	BP_OnStrengthChange(strength, maxStrength);
}

void AQCharacterBase::AutoAssignTeamID()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = PLAYER_TEAM_ID;
	}
	else
	{
		TeamID = ENEMY_TEAM_ID;
	}
}

void AQCharacterBase::Die()
{
	if (APlayerController* pc = Cast<APlayerController>(GetController()))
	{
		pc->DisableInput(pc);
	}
	if (AAIController* aic = Cast<AAIController>(GetController()))
	{
		aic->GetBrainComponent()->StopLogic(TEXT("Die"));
	}
}

