// Erades

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {

	// UKismetSystemLibrary::PrintString(this, FString("Ability activated from c++!"), true, true, FColor::Yellow, 3.0f);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//if (SpawnProjectile(ActivationInfo)) return;
}

bool UAuraProjectileSpell::SpawnProjectile() {
	const bool bHasAuthority = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bHasAuthority) {
		return true;
	}
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface) {
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		// TODO: Set rotation.
		SpawnTransform.SetLocation(SocketLocation);
		AAuraProjectile* ProjectileDeferred = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give the projectile a gameplay effect spec for causing damage.
		ProjectileDeferred->FinishSpawning(SpawnTransform);
	}
	return false;
}