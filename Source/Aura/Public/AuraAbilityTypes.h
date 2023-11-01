// Erades

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"

#include "AuraAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){};

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC;

	UPROPERTY()
	float BaseDamage = 0.f;

	UPROPERTY()
	float AbilityLevel = 1.f;

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();

	UPROPERTY()
	float DebuffChance = 0.f;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;
};

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsCriticalHit() const { return (bIsCriticalHit); }
	bool IsBlockedHit() const { return (bIsBlockedHit); }
	bool IsSuccessfulDebuff() const { return (bIsSuccessfulDebuff); }
	float GetDebuffDamage() const { return (DebuffDamage); }
	float GetDebuffDuration() const { return (DebuffDuration); }
	float GetDebuffFrequency() const { return (DebuffFrequency); }
	TSharedPtr<FGameplayTag> GetDamageType() const { return (DamageType); }

	void SetIsCriticalHit(const bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(const bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetSuccessfulDebuff(const bool Value) { bIsSuccessfulDebuff = Value; }
	void SetDebuffDamage(const float Value) { DebuffDamage = Value; }
	void SetDebuffDuration(const float Value) { DebuffDuration = Value; }
	void SetDebuffFrequency(const float Value) { DebuffFrequency = Value; }
	void SetDamageType(const TSharedPtr<FGameplayTag>& Value) { DamageType = Value; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return (StaticStruct());
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FAuraGameplayEffectContext* Duplicate() const override
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	float DebuffDamage = 0;

	UPROPERTY()
	float DebuffDuration = 0;

	UPROPERTY()
	float DebuffFrequency = 0;

	TSharedPtr<FGameplayTag> DamageType;
};

template <>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

struct FAuraDamagePairing
{
public:
	static const FAuraDamagePairing& Get()
	{
		return (DamagePairing);
	}
	static void InitializePairingInfo();

	TMap<FGameplayTag, FGameplayTag> DamageTypeToResistances;
	TMap<FGameplayTag, FGameplayTag> DamageTypeToDebuffs;

private:
	static FAuraDamagePairing DamagePairing;
};
