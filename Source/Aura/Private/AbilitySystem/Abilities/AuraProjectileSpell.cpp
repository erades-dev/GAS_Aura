// Erades

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// UKismetSystemLibrary::PrintString(this, FString("Ability activated from c++!"), true, true, FColor::Yellow, 3.0f);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// if (SpawnProjectile(ActivationInfo)) return;
}

bool UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bHasAuthority = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bHasAuthority)
	{
		return (true);
	}
	FTransform SpawnTransform;
	const FVector Location = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		FAuraGameplayTags::Get().Montage_Attack_Weapon);
	FRotator Rotation = (ProjectileTargetLocation - Location).Rotation();
	// Rotation.Pitch = 0.f;
	SpawnTransform.SetLocation(Location);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	AAuraProjectile* ProjectileDeferred = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,
		GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(ProjectileDeferred);

	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}

	ProjectileDeferred->DamageEffectSpecHandle = SpecHandle;
	ProjectileDeferred->FinishSpawning(SpawnTransform);
	return (false);
}