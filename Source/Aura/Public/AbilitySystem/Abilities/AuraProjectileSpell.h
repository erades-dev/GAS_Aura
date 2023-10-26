// Erades

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageGameplayAbility.h"

#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
/**
 *
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GAS|Projectile")
	bool SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Projectile")
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
