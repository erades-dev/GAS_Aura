// Erades

#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	TArray<FVector> SpawnLocations;
	const AActor* Actor = GetAvatarActorFromActorInfo();
	const FVector Forward = Actor->GetActorForwardVector();
	const FVector Location = Actor->GetActorLocation();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread * 0.5f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread * 0.5f, FVector::UpVector);
	const float DeltaSpread = SpawnSpread / (NumMinions - 1);

	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector RndLocation = Location + Direction * FMath::RandRange(SpawnMinDistance, SpawnMaxDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, RndLocation + FVector(0.f, 0.f, 400.f), RndLocation + FVector(0.f, 0.f, -400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			SpawnLocations.Add(Hit.ImpactPoint);
		}
	}
	return (SpawnLocations);
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return (MinionClasses[Selection]);
}
