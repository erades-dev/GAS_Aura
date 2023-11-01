// Erades

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// UKismetSystemLibrary::PrintString(this, FString("Ability activated from c++!"), true, true, FColor::Yellow, 3.0f);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// if (SpawnProjectile(ActivationInfo)) return;
}

bool UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
		return (true);

	FTransform SpawnTransform;
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
		Rotation.Pitch = PitchOverride;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	AAuraProjectile* ProjectileDeferred = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,
		GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	ProjectileDeferred->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	ProjectileDeferred->FinishSpawning(SpawnTransform);
	return (false);
}

/*const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
EffectContextHandle.SetAbility(this);
EffectContextHandle.AddSourceObject(ProjectileDeferred);
const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageType, ScaledDamage);
ProjectileDeferred->DamageEffectParams = SpecHandle;*/