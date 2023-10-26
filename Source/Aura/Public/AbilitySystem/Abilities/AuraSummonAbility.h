// Erades

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 *
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category = "GAS|Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Summoning")
	int32 NumMinions = 5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Summoning")
	float SpawnMinDistance = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Summoning")
	float SpawnMaxDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Summoning")
	float SpawnSpread = 90.f;
};
