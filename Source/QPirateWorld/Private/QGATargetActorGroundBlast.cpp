// Fill out your copyright notice in the Description page of Project Settings.


#include "QGATargetActorGroundBlast.h"
#include "Abilities/GameplayAbility.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"

AQGATargetActorGroundBlast::AQGATargetActorGroundBlast()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComp->SetupAttachment(RootComp);
	DecalComp->DecalSize = FVector(Radius);
}

void AQGATargetActorGroundBlast::StartTargeting(UGameplayAbility* Ability)
{
	//Super::StartTargeting(Ability);
	OwningAbility = Ability;

	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	DecalComp->DecalSize = FVector(Radius);

}

void AQGATargetActorGroundBlast::ConfirmTargetingAndContinue()
{
	FVector blastAreaLocation;
	GetLookAtPoint(blastAreaLocation);

#pragma region FindBlastAreaOverlapEnemies
	TArray<FOverlapResult> overlapResults;
	TArray<TWeakObjectPtr<AActor>> overlappingActors;

	bool bTraceComplex = false;
	FCollisionQueryParams queryParams;
	queryParams.bTraceComplex = bTraceComplex;
	if (APawn* masterPawn = MasterPC->GetPawn())
	{
		queryParams.AddIgnoredActor(masterPawn->GetUniqueID());
	}

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


#pragma region GenerateTargetDataContainsDecalLocation
	FGameplayAbilityTargetData_LocationInfo* targetData_location = new FGameplayAbilityTargetData_LocationInfo();
	targetData_location->TargetLocation.LiteralTransform = DecalComp->GetComponentTransform();
	targetData_location->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
#pragma endregion



	if (overlappingActors.Num() > 0)
	{
		//FGameplayAbilityTargetData
		FGameplayAbilityTargetDataHandle targetDataHandle = StartLocation.MakeTargetDataHandleFromActors(overlappingActors);
		targetDataHandle.Add(targetData_location);
		TargetDataReadyDelegate.Broadcast(targetDataHandle);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle(targetData_location));
	}
}

bool AQGATargetActorGroundBlast::GetLookAtPoint(FVector& outLookAtLocation)
{
	check(MasterPC);
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	MasterPC->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	FCollisionQueryParams querayParams;
	querayParams.bTraceComplex = true;
	if (APawn* masterPawn = MasterPC->GetPawn())
	{
		querayParams.AddIgnoredActor(masterPawn->GetUniqueID());
	}


	FVector lookAtPoint = FVector::ZeroVector;
	FHitResult hitRes;
	GetWorld()->LineTraceSingleByChannel(hitRes,
		ViewPointLocation, ViewPointLocation + ViewPointRotation.Vector() * 10000.0f, ECC_Visibility, querayParams);
	if (hitRes.bBlockingHit)
	{
		lookAtPoint = hitRes.ImpactPoint;
	}

	outLookAtLocation = lookAtPoint;
	return hitRes.bBlockingHit;
}

void AQGATargetActorGroundBlast::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector lookAtlocation;
	bool success = GetLookAtPoint(lookAtlocation);
	//UE_LOG(LogTemp, Warning, TEXT("lookAtlocation = %s "), *lookAtlocation.ToString());
	if (success)
	{
		//DrawDebugSphere(GetWorld(), lookAtlocation, Radius, 32, FColor::Red, false, 5.0f, 0, 5.0f);
		DecalComp->SetWorldLocation(lookAtlocation);
	}
}

