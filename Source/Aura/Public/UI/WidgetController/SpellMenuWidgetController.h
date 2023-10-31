// Erades

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnable, bool, bEquipButtonEnable);

//struct FGameplayTag;
/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Spell Menu")
	FOnIntChangedSignature SpellPointsChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Spell Menu")
	FSpellGlobeSelectedSignature OnSpellGlobeSelectedDelegate;

	// Begin UAuraWidgetController override.
	virtual void BroadCastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	void TryToSpendPointOnAbility();

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

private:

	FGameplayTag SelectedAbility;
};
