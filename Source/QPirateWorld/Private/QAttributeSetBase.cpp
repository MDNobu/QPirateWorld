// Fill out your copyright notice in the Description page of Project Settings.


#include "QAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

UQAttributeSetBase::UQAttributeSetBase()
{

}

void UQAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& data)
{
	Super::PostGameplayEffectExecute(data);

	Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetBaseValue()));
	Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
	Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.0f, MaxMana.GetBaseValue()));
	Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));
	Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.0f, MaxStrength.GetBaseValue()));
	Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.0f, MaxStrength.GetCurrentValue()));


	UProperty* targetProperty = data.EvaluatedData.Attribute.GetUProperty();
	UProperty* healthProperty = FindFieldChecked<UProperty>(
		UQAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UQAttributeSetBase, Health));
	UProperty* manaProperty = FindFieldChecked<UProperty>(
		UQAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UQAttributeSetBase, Mana));
	UProperty* strengthProperty = FindFieldChecked<UProperty>(
		UQAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UQAttributeSetBase, Strength));

	if (targetProperty == healthProperty)
	{
		UE_LOG(LogTemp, Warning, TEXT("ouch, taking damage health left %f"), Health.GetCurrentValue());
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	} else if (targetProperty == manaProperty)
	{
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	} else if ( targetProperty == strengthProperty)
	{
		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}
