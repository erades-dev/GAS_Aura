// Erades

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 *
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;

protected:

	UFUNCTION(BlueprintPure)
	static FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
	float DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
	float DebuffDuration = 5.f;

};
