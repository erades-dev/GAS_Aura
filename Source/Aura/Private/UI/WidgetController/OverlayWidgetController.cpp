// Erades

#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AuraPlayerState->OnXpChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnPlayerXpChanged);
	AuraPlayerState->OnLevelChangedDelegate.AddLambda([this](const int32 NewLevel) {
		OnPlayerLevelChanged.Broadcast(NewLevel);
	});

	if (AuraAbilitySystemComponent->bStartupAbilitiesGiven)
	{
		BroadcastAbilityInfo();
	}
	else
	{
		AuraAbilitySystemComponent->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
	}
	AuraAbilitySystemComponent->EffectAssetTagsDelegate.AddLambda([this](const FGameplayTagContainer& AssetTags) {
		for (FGameplayTag Tag : AssetTags)
		{
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {
			OnManaChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});
}

void UOverlayWidgetController::OnPlayerXpChanged(const int32 NewXp) const
{
	const ULevelUpInfo* LevelUpInfo = AuraPlayerState->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unable to retieve LevelUpInfo. Please fill out in AuraPlayerState Blueprint"));

	const int32 LevelReach = LevelUpInfo->FindLevelForXp(NewXp);

	const int32 LevelMaxXp = LevelUpInfo->LevelUpInformation[LevelReach].Xp;
	const int32 LevelMinXp = LevelUpInfo->LevelUpInformation[LevelReach - 1].Xp;
	const int32 LevelDeltaXp = LevelMaxXp - LevelMinXp;

	const int32 CurrentLevelProgress = NewXp - LevelMinXp;

	const float NewPercent = static_cast<float>(CurrentLevelProgress) / static_cast<float>(LevelDeltaXp);
	OnXpPercentChanged.Broadcast(NewPercent);
}
