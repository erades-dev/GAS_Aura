// Erades

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <AbilitySystemInterface.h>
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

	UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();

	// Begin APlayerState override.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return (AttributeSet); }

	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnXpChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;

	// TODO: Level redundant on State and PlayerCharacter
	int32 GetLevel() const { return (Level); };
	int32 GetXp() const { return (Xp); };
	int32 GetAttributePoints() const { return (AttributePoints); };
	int32 GetSpellPoints() const { return (SpellPoints); };

	void AddToLevel(const int32 Amount);
	void SetLevel(const int32 Value);

	void AddToXp(const int32 Amount);
	void SetXp(const int32 Value);

	void AddToAttributePoints(const int32 Value);
	void SetAttributePoints(const int32 Value);

	void AddToSpellPoints(const int32 Value);
	void SetSpellPoints(const int32 Value);
	// TODO: Encapsulate these Stats in a shared class.

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Xp)
	int32 Xp = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoints)
	int32 SpellPoints = 0;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_Xp(int32 OldXp);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldXp);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldXp);
};
