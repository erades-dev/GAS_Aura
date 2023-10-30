// Erades

#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	// TODO: swap all collisions to the capsule.
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_PROJECTILE, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

ECharacterClass AAuraCharacterBase::GetCharacterClass_Implementation()
{
	return (CharacterClass);
}

int32 AAuraCharacterBase::GetCharacterLevel_Implementation()
{
	return (CharacterLevel);
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
	return (bDead);
}

AActor* AAuraCharacterBase::GetAvatar_Implementation()
{
	return (this);
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	if (MontageTag.MatchesTagExact(TAG_CombatSocket_Weapon) && IsValid(Weapon))
	{
		return (Weapon->GetSocketLocation(WeaponTipSocketName));
	}
	if (MontageTag.MatchesTagExact(TAG_CombatSocket_LeftHand))
	{
		return (GetMesh()->GetSocketLocation(LeftHand));
	}
	if (MontageTag.MatchesTagExact(TAG_CombatSocket_RightHand))
	{
		return (GetMesh()->GetSocketLocation(RightHand));
	}
	return (FVector());
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return (AbilitySystemComponent);
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return (HitReactMontage);
}

TArray<FTaggedMontage> AAuraCharacterBase::GetAttackMontages_Implementation()
{
	return (AttackMontages);
}

UNiagaraSystem* AAuraCharacterBase::GetBloodEffect_Implementation()
{
	return (BloodEffect);
}

FTaggedMontage AAuraCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (auto TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return (TaggedMontage);
		}
	}
	return (FTaggedMontage());
}

int32 AAuraCharacterBase::GetMinionCount_Implementation()
{
	return (MinionCount);
}

void AAuraCharacterBase::IncrementMinionCount_Implementation(const int32 Amount)
{
	MinionCount += Amount;
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();

	bDead = true;

	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, const float Level) const
{
	check(IsValid(AbilitySystemComponent));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1);
	ApplyEffectToSelf(TransientAttributes, 1);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority())
		return;
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->AddCharacterAbilities(StartupAbilities);
	AuraASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}

void AAuraCharacterBase::Dissolve()
{
	TArray<UMaterialInstanceDynamic*> DynamicMaterials;
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		DynamicMaterials.Add(DynamicMatInst);
	}

	if (IsValid(DissolveMaterialInstanceWeapon))
	{
		UMaterialInstanceDynamic* DynamicMatInstWeapon = UMaterialInstanceDynamic::Create(DissolveMaterialInstanceWeapon, Weapon);
		Weapon->SetMaterial(0, DynamicMatInstWeapon);
		DynamicMaterials.Add(DynamicMatInstWeapon);
	}
	StartDissolveTimeline(DynamicMaterials);
}
