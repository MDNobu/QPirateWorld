// Fill out your copyright notice in the Description page of Project Settings.


#include "QCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "QAttributeSetBase.h"
#include "AIController.h"
#include "QGameplayAbilityBase.h"
#include "QPlayerControllerBase.h"
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

	AddGameplayTag(GetFullHealthTag());
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

void AQCharacterBase::AcquireAbility(TSubclassOf<UGameplayAbility> abilityToAquire)
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


void AQCharacterBase::AcquireAbilities(TArray<TSubclassOf<UGameplayAbility>> abilitiesToAcquire)
{
	for (TSubclassOf<UGameplayAbility> ability : abilitiesToAcquire)
	{
		AcquireAbility(ability);

		//ability如果是QGameplayAbility的子对象，加入UI
		if (ability->IsChildOf(UQGameplayAbilityBase::StaticClass()))
		{
			if (TSubclassOf<UQGameplayAbilityBase> abilityBase = ability.Get())
			{
				AddToHUDAbilitySlot(abilityBase);
			}
		}
	}
}

bool AQCharacterBase::IsHostile(AQCharacterBase* other) const
{
	bool bHostile = false;
	bHostile = other && (other->TeamID != this->TeamID);
	return bHostile;
}

void AQCharacterBase::AddGameplayTag(const FGameplayTag& tagToAdd)
{
	AbilitySystemComp->AddLooseGameplayTag(tagToAdd);
	AbilitySystemComp->SetTagMapCount(tagToAdd, 1);
}

void AQCharacterBase::RemoveGameplayTag(const FGameplayTag& tagToRemove)
{
	AbilitySystemComp->RemoveLooseGameplayTag(tagToRemove);
}

void AQCharacterBase::TryStun(float stunDuration)
{
	if (stunDuration <= 0)
	{
		return;
	}

	DisableControlInput();
	GetWorldTimerManager().SetTimer(StunTimerHandle, this, &AQCharacterBase::EnableControlInput, stunDuration, false);
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
	DisableControlInput();
}

void AQCharacterBase::DisableControlInput()
{
	if (APlayerController* pc = Cast<APlayerController>(GetController()))
	{
		pc->DisableInput(pc);
	}
	if (AAIController* aic = Cast<AAIController>(GetController()))
	{
		if (aic->GetBrainComponent())
		{
			aic->GetBrainComponent()->StopLogic(TEXT("Die"));
		}
	}
}

void AQCharacterBase::EnableControlInput()
{
	if (bIsDead)
	{
		return;
	}

	if (APlayerController* pc = Cast<APlayerController>(GetController()))
	{
		//pc->DisableInput(pc);
		pc->EnableInput(pc);
	}
	if (AAIController* aic = Cast<AAIController>(GetController()))
	{
		if (aic->GetBrainComponent())
		{
			//aic->GetBrainComponent()->StopLogic(TEXT("Die"));
			aic->GetBrainComponent()->RestartLogic();
		}
	}
}

void AQCharacterBase::AddToHUDAbilitySlot(TSubclassOf<UQGameplayAbilityBase> abilityToAdd)
{
	if (AQPlayerControllerBase* playerController = Cast<AQPlayerControllerBase>(GetController()) )
	{
		UQGameplayAbilityBase* abilityInstance = abilityToAdd.Get()->GetDefaultObject<UQGameplayAbilityBase>();
		if (abilityInstance)
		{
			playerController->AddToHUDAbilitySlot(abilityInstance->QueryAbilityInfo());
		}
	}
}

