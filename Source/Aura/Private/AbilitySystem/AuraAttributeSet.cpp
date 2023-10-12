// Erades

#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include <Net/UnrealNetwork.h>
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet() {
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(55.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> &OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data) {
	Super::PostGameplayEffectExecute(Data);

	// Source = cause of the effect, Target = target of the effect(owner of this AS)
	const FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	const UAbilitySystemComponent *SourceASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(SourceASC) && SourceASC->AbilityActorInfo.IsValid() && SourceASC->AbilityActorInfo->AvatarActor.IsValid()) {
		AActor *SourceAvatarActor = SourceASC->AbilityActorInfo->AvatarActor.Get();
		const AController *SourceController = SourceASC->AbilityActorInfo->PlayerController.Get();
		if (!SourceController && SourceAvatarActor) {
			if (const APawn *Pawn = Cast<APawn>(SourceAvatarActor)) {
				SourceController = Pawn->GetController();
			}
		}
		if (SourceController) {
			ACharacter *SourceCharacter = Cast<ACharacter>(SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid()) {
		AActor *TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AController *TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		ACharacter *TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
		UAbilitySystemComponent *TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
	}

	// if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
	//	UE_LOG(LogTemp, Warning, TEXT("Health form get Health(): %f"), GetHealth());
	//	UE_LOG(LogTemp, Warning, TEXT("Magnitude: %f"), Data.EvaluatedData.Magnitude);
	// }
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData &OldHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData &OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData &OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}
