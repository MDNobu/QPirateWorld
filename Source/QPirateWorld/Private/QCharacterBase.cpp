// Fill out your copyright notice in the Description page of Project Settings.


#include "QCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "QAttributeSetBase.h"

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


void AQCharacterBase::OnHealthChange(float health, float maxHealth)
{
	BP_OnHealthChange(health, maxHealth);
}

