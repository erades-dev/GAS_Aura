// Erades

#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraLogChannels.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void USpellMenuWidgetController::BroadCastInitialValues()
{

	BroadcastAbilityInfo();
	SpellPointsChangedDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	AuraAbilitySystemComponent->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag) {
		if (AbilityInfo)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoByTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	AuraPlayerState->OnSpellPointsChangedDelegate.AddLambda([this](const int32 Points) {
		SpellPointsChangedDelegate.Broadcast(Points);
	});
}

void USpellMenuWidgetController::TryToSpendPointOnAbility()
{
	FGameplayAbilitySpec* Spec = AuraAbilitySystemComponent->GetSpecFromAbilityTag(SelectedAbility);
	if (!Spec)
		return;
	FGameplayTag Status = AuraAbilitySystemComponent->GetStatusFromSpec(*Spec);
	UE_LOG(LogAura, Log, TEXT("Selected ability status: [%s]"), *Status.ToString());
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	SelectedAbility = AbilityTag;

	// TODO: chapter 289.
	const int32 SpellPoints = AuraPlayerState->GetSpellPoints();
	bool bTagValid = AbilityTag.IsValid();

	if (AuraAbilitySystemComponent->GetSpecFromAbilityTag(AbilityTag))
	{
	}

	bool bEquipButtonEnable = false;
	bool bSpendPointsButtonEnable = false;
	OnSpellGlobeSelectedDelegate.Broadcast(bSpendPointsButtonEnable, bEquipButtonEnable);
}
