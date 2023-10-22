// Erades

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <AbilitySystemInterface.h>

#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	// Begin Combat Interface.
	virtual FVector GetCombatSocketLocation() override;
	virtual void Die() override;

	// Begin AbilitySystem Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	UAttributeSet* GetAttributeSet() const { return (AttributeSet); };

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

protected:
	// Begin ACharacter Override.
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();
	virtual void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	void AddCharacterAbilities();
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(const TArray<UMaterialInstanceDynamic*>& DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, Category = "GAS|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "GAS|Combat")
	FName WeaponTipSocketName;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
	TSubclassOf<UGameplayEffect> TransientAttributes;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstanceWeapon;

private:
	UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS|Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
