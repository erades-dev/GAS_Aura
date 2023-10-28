// Erades

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <AbilitySystemInterface.h>

#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UNiagaraSystem;
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
	virtual void Die() override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual int32 GetCharacterLevel_Implementation() override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;

	// Begin AbilitySystem Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "GAS|Combat|Socket")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category = "GAS|Combat|Socket")
	FName LeftHand;

	UPROPERTY(EditAnywhere, Category = "GAS|Combat|Socket")
	FName RightHand;

	UPROPERTY(EditAnywhere, Category = "GAS|Combat|Socket")
	TArray<FTaggedMontage> AttackMontages;

	UPROPERTY(EditAnywhere, Category = "GAS|Visual")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "GAS|Visual")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstanceWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Visual")
	UNiagaraSystem* BloodEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Visual")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Character")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Character")
	int32 CharacterLevel = 1;

	bool bDead = false;

	int32 MinionCount = 0;

private:
	UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS|Combat|Montage")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
