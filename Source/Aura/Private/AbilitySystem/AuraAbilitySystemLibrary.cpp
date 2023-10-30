// Erades

#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams OutWidgetControllerParams;
	AAuraHUD* AuraHUD = MakeWidgetControllerParams(WorldContextObject, OutWidgetControllerParams);
	if (AuraHUD)
	{
		return (AuraHUD->GetOverlayWidgetController(OutWidgetControllerParams));
	}
	return (nullptr);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams OutWidgetControllerParams;
	AAuraHUD* AuraHUD = MakeWidgetControllerParams(WorldContextObject, OutWidgetControllerParams);
	if (AuraHUD)
	{
		return (AuraHUD->GetAttributeMenuWidgetController(OutWidgetControllerParams));
	}
	return (nullptr);
}

USpellMenuWidgetController* UAuraAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams OutWidgetControllerParams;
	AAuraHUD* AuraHUD = MakeWidgetControllerParams(WorldContextObject, OutWidgetControllerParams);
	if (AuraHUD)
	{
		return (AuraHUD->GetSpellMenuWidgetController(OutWidgetControllerParams));
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

void UAuraAbilitySystemLibrary::GiveStartupAbilities(
	const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo)
		return;

	for (const auto Ability : CharacterClassInfo->CommonAbilities)
	{
		// By design these abilities will not have level, for now.
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		ASC->GiveAbility(AbilitySpec);
	}

	for (const auto Ability : CharacterClassInfo->GetClassDefaultInfo(CharacterClass).StartupAbilities)
	{
		int CharacterLevel = 1;
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			CharacterLevel = ICombatInterface::Execute_GetCharacterLevel(ASC->GetAvatarActor());
		}
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, CharacterLevel);
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

UAbilityInfo* UAuraAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AuraGameModeBase)
	{
		return (AuraGameModeBase->AbilityInfo);
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

void UAuraAbilitySystemLibrary::GetLifePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors,
	const TArray<AActor*>& ActorsToIgnore, const float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	TArray<FOverlapResult> Overlaps;
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		World->OverlapMultiByObjectType(
			Overlaps,
			SphereOrigin,
			FQuat::Identity,
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
			FCollisionShape::MakeSphere(Radius),
			SphereParams);
	}
	for (FOverlapResult Overlap : Overlaps)
	{
		AActor* Actor = Overlap.GetActor();
		if (Actor->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Actor))
		{
			OutOverlappingActors.AddUnique(Actor);
		}
	}
}

bool UAuraAbilitySystemLibrary::IsNotFriend(const AActor* ActorA, const AActor* ActorB)
{
	const bool bBothArePlayer = ActorA->ActorHasTag(FName("Player")) && ActorB->ActorHasTag(FName("Player"));
	const bool bBothAreEnemy = ActorA->ActorHasTag(FName("Enemy")) && ActorB->ActorHasTag(FName("Enemy"));
	const bool bFriends = (bBothArePlayer || bBothAreEnemy);
	return (!bFriends);
}

int32 UAuraAbilitySystemLibrary::GetXpRewardFromClassAndLevel(const UObject* WorldContextObject, const ECharacterClass CharacterClass, const int32 Level)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo)
		return (0);

	const FCharacterClassDefaultInfo Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XpReward = Info.XpReward.GetValueAtLevel(Level);
	return (static_cast<int32>(XpReward));
}

AAuraHUD* UAuraAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& WidgetControllerParams)
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

			WidgetControllerParams.PlayerController = PlayerController;
			WidgetControllerParams.PlayerState = AuraPlayerState;
			WidgetControllerParams.AbilitySystemComponent = AbilitySystemComponent;
			WidgetControllerParams.AttributeSet = AttributeSet;
			return (AuraHUD);
		}
	}
	return (nullptr);
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