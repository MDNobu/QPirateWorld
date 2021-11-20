// Fill out your copyright notice in the Description page of Project Settings.


#include "QAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

UQAttributeSetBase::UQAttributeSetBase()
{

}

void UQAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	UProperty* targetProperty = Data.EvaluatedData.Attribute.GetUProperty();

	//UProperty* healthProperty = FindFieldChecked<UProperty>(
	//	UQAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UQAttributeSetBase, Health));


	UProperty* healthProperty = FindFieldChecked<UProperty>(
		UQAttributeSetBase::StaticClass(), FName(TEXT("Health")));

	if (targetProperty == healthProperty)
	{
		UE_LOG(LogTemp, Warning, TEXT("ouch, taking damage health left %f"), Health.GetCurrentValue());
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}
}
