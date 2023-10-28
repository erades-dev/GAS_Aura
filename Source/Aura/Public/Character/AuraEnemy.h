// Erades

#pragma once

#include <CoreMinimal.h>
#include <Interaction/EnemyInterface.h>
#include <UI/WidgetController/OverlayWidgetController.h>

#include "Character/AuraCharacterBase.h"
#include "AuraEnemy.generated.h"

class UBehaviorTree;
class AAuraAIController;
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
	// Begin ACharacter Override.
	virtual void PossessedBy(AController* NewController) override;

	// Begin IEnemyInterface.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	// Begin ICombatInterface.
	virtual void Die() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintAssignable)
	FOnFloatChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnFloatChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Combat")
	bool bHitReacting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Combat")
	float BaseWalkSpeed = 250.0f;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Combat")
	float LifeSpan = 5.0f;

	UPROPERTY(BlueprintReadWrite, Category = "GAS|Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	// Begin AAuraCharacterBase override.
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	void InitializeBindings();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
};
