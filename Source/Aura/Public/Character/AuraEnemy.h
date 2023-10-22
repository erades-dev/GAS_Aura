// Erades

#pragma once

#include <CoreMinimal.h>
#include <Interaction/EnemyInterface.h>
#include <UI/WidgetController/OverlayWidgetController.h>
#include <AbilitySystem/Data/CharacterClassInfo.h>

#include "Character/AuraCharacterBase.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 *
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	// Begin Enemy Interface.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// End Enemy Interface.

	// Begin Combat Interface.
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	// End Combat Interface.

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Combat")
	bool bHitReaction;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Combat")
	float BaseWalkSpeed = 250.0f;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Combat")
	float LifeSpan = 5.0f;

protected:
	// Begin AAuraCharacterBase override.
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	// End AAuraCharacterBase override.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Character Class Defaults")
	int32 CharacterLevel = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

private:
	void InitializeBindings();
};
