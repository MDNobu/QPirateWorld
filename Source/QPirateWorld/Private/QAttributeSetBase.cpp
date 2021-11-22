// Fill out your copyright notice in the Description page of Project Settings.


#include "QAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "QCharacterBase.h"

UQAttributeSetBase::UQAttributeSetBase()
{

}

void UQAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& data)
{
	Super::PostGameplayEffectExecute(data);


	UProperty* targetProperty = data.EvaluatedData.Attribute.GetUProperty();
	UProperty* healthProperty = FindFieldChecked<UProperty>(
		UQAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UQAttributeSetBase, Health));
	UProperty* manaProperty = FindFieldChecked<UProperty>(
		UQAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UQAttributeSetBase, Mana));
	UProperty* strengthProperty = FindFieldChecked<UProperty>(
		UQAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UQAttributeSetBase, Strength));

	if (targetProperty == healthProperty)
	{
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetBaseValue()));
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));

		AQCharacterBase* character = Cast<AQCharacterBase>(GetOwningActor());
		if (Health.GetCurrentValue() >= MaxHealth.GetCurrentValue())
		{
			character->AddGameplayTag(character->GetFullHealthTag());
		}
		else
		{
			character->RemoveGameplayTag(character->GetFullHealthTag());
		}

		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
		UE_LOG(LogTemp, Warning, TEXT("ouch, taking damage health left %f"), Health.GetCurrentValue());
	} else if (targetProperty == manaProperty)
	{
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.0f, MaxMana.GetBaseValue()));
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));

		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
		UE_LOG(LogTemp, Warning, TEXT(" mana left %f"), Mana.GetCurrentValue());
	} else if ( targetProperty == strengthProperty)
	{
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.0f, MaxStrength.GetBaseValue()));
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.0f, MaxStrength.GetCurrentValue()));

		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}
