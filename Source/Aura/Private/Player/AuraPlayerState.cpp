// Erades

#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <AbilitySystem/AuraAttributeSet.h>

#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	LevelUpInfo = CreateDefaultSubobject<ULevelUpInfo>("LevelUpInfo");

	NetUpdateFrequency = 100.0f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, Xp);
	DOREPLIFETIME(AAuraPlayerState, AttributePoints);
	DOREPLIFETIME(AAuraPlayerState, SpellPoints);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return (AbilitySystemComponent);
}

void AAuraPlayerState::AddToLevel(const int32 Amount)
{
	SetLevel(Level + Amount);
}

void AAuraPlayerState::SetLevel(const int32 Value)
{
	if (!HasAuthority())
		return;
	Level = Value;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToXp(const int32 Amount)
{
	SetXp(Xp + Amount);
}

void AAuraPlayerState::SetXp(const int32 Value)
{
	if (!HasAuthority())
		return;
	Xp = Value;
	OnXpChangedDelegate.Broadcast(Xp);
}

void AAuraPlayerState::AddToAttributePoints(const int32 Value)
{
	SetAttributePoints(AttributePoints + Value);
}

void AAuraPlayerState::SetAttributePoints(const int32 Value)
{
	AttributePoints = Value;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(const int32 Value)
{
	SetSpellPoints(SpellPoints + Value);
}

void AAuraPlayerState::SetSpellPoints(const int32 Value)
{
	SpellPoints = Value;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_Xp(int32 OldXp)
{
	OnXpChangedDelegate.Broadcast(Xp);
}

void AAuraPlayerState::OnRep_AttributePoints(int32 OldXp)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoints(int32 OldXp)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
