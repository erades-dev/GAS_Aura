// Erades

#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"

#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadCastInitialValues()
{
	for (const auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		BroadCastAttributeInfo(Pair.Key, Pair.Value());
	}
	AttributePointsChangedDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
	SpellPointsChangedDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value())
			.AddLambda([this, Pair](const FOnAttributeChangeData& Data) {
				BroadCastAttributeInfo(Pair.Key, Pair.Value());
			});
	}

	AuraPlayerState->OnAttributePointsChangedDelegate.AddLambda([this](const int32 Points) {
		AttributePointsChangedDelegate.Broadcast(Points);
	});
	AuraPlayerState->OnSpellPointsChangedDelegate.AddLambda([this](const int32 Points) {
		SpellPointsChangedDelegate.Broadcast(Points);
	});
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	AuraAbilitySystemComponent->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadCastAttributeInfo(const FGameplayTag AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfoDataAsset->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
