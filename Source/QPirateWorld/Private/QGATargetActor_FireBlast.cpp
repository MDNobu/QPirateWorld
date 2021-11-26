// Fill out your copyright notice in the Description page of Project Settings.


#include "QGATargetActor_FireBlast.h"
#include "Abilities/GameplayAbility.h"


void AQGATargetActor_FireBlast::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AQGATargetActor_FireBlast::ConfirmTargetingAndContinue()
{
	APawn* playerPawn = MasterPC->GetPawn();
	if (!playerPawn)
	{
		return;
	}

	FVector blastAreaLocation = playerPawn->GetActorLocation();

#pragma region FindBlastAreaOverlapEnemies
	TArray<FOverlapResult> overlapResults;
	TArray<TWeakObjectPtr<AActor>> overlappingActors;

	bool bTraceComplex = false;
	FCollisionQueryParams queryParams;
	queryParams.bTraceComplex = bTraceComplex;
	queryParams.AddIgnoredActor(playerPawn->GetUniqueID());

	bool  bOverlaped = GetWorld()->OverlapMultiByObjectType(
		overlapResults,
		blastAreaLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(Radius), queryParams);

	if (bOverlaped)
	{
		for (const FOverlapResult& overlapRes : overlapResults)
		{
			APawn* overlapPawn = Cast<APawn>(overlapRes.GetActor());
			if (overlapPawn && !overlappingActors.Contains(overlapPawn))
			{
				overlappingActors.Add(overlapPawn);
			}
		}
	}
#pragma endregion


	if (overlappingActors.Num() > 0)
	{
		//FGameplayAbilityTargetData
		FGameplayAbilityTargetDataHandle targetDataHandle = StartLocation.MakeTargetDataHandleFromActors(overlappingActors);
		TargetDataReadyDelegate.Broadcast(targetDataHandle);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}
