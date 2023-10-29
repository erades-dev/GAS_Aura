// Erades

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
/**
 *
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	// Begin ACharacter override.
	virtual void PossessedBy(AController* NewController) override;

	// Begin APAwn override.
	virtual void OnRep_PlayerState() override;

	// Begin AAuraCharacterBase override.
	virtual int32 GetCharacterLevel_Implementation() override;
	// TODO: CharacterBase has a level that is ignored for PlayerCharacter wich uses level from player state.
	// TODO: that could lead to confusion. Since level is used for combat. Mybe CharacterBase level should get its value from state.

	// Begin IPlayerInterface override.
	virtual int32 GetXp_Implementation() override;
	virtual int32 GetRewardAttributePoints_Implementation(const int32 Level) const override;
	virtual int32 GetRewardSpellPoints_Implementation(const int32 Level) const override;
	virtual int32 GetAttributePoints_Implementation() const override;
	virtual int32 GetSpellPoints_Implementation() const override;
	virtual void AddToPLayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddXp_Implementation(int32 InXp) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	virtual int32 FindLevelForXp_Implementation(int32 InXp) override;
	virtual void LevelUp_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Player|LevelUp")
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

private:
	virtual void InitAbilityActorInfo() override;

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastLevelUpParticles() const;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
};
