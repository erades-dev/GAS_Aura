// Erades

#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (PlayerController)
	{
		const auto AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD());
		if (AuraHUD)
		{
			AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			return (AuraHUD->GetOverlayWidgetController(WidgetControllerParams));
		}
	}
	return (nullptr);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (PlayerController)
	{
		const auto AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD());
		if (AuraHUD)
		{
			AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			return (AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams));
		}
	}
	return (nullptr);
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(
	const UObject* WorldContextObject, const ECharacterClass CharacterClass, const float Level, UAbilitySystemComponent* ASC)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo)
		return;

	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	Context.AddSourceObject(ASC->GetAvatarActor());
	const FGameplayEffectSpecHandle PrimarySpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, Context);
	const FGameplayEffectSpecHandle SecondarySpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, Context);
	const FGameplayEffectSpecHandle TransientSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->TransientAttributes, Level, Context);

	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandle.Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*TransientSpecHandle.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo)
		return;

	for (const auto Ability : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AuraGameModeBase)
	{
		return (AuraGameModeBase->CharacterClassInfo);
	}
	return (nullptr);
}

bool UAuraAbilitySystemLibrary::IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get());
	if (AuraEffectContext)
	{
		return (AuraEffectContext->IsBlockedHit());
	}
	return (false);
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get());
	if (AuraEffectContext)
	{
		return (AuraEffectContext->IsCriticalHit());
	}
	return (false);
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsBlockedHit)
{
	FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get());
	if (AuraEffectContext)
	{
		AuraEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsBlockedHit)
{
	FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get());
	if (AuraEffectContext)
	{
		AuraEffectContext->SetIsCriticalHit(bInIsBlockedHit);
	}
}

// void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level,
// UAbilitySystemComponent* ASC) {
//	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
//	if (AuraGameMode == nullptr)
//		return;
//
//	AActor* AvatarActor = ASC->GetAvatarActor();
//
//	UCharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
//	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
//
//	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
//	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
//	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level,
// PrimaryAttributesContextHandle); 	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
//
//	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
//	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
//	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level,
// SecondaryAttributesContextHandle); 	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
//
//	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
//	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
//	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->TransientAttributes, Level,
// VitalAttributesContextHandle); 	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
// }