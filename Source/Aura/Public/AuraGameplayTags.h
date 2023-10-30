// Erades

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

/**
 * AuraGameplayTags
 * Singleton containing native Gameplay Tags.
 */

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Input_Passive_3);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Abilities_Status_Equipped);

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get()
	{
		return (GameplayTags);
	}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	FGameplayTag Attributes_Transient_Health;
	FGameplayTag Attributes_Transient_Mana;

	FGameplayTag Attributes_Meta_IncomingXp;

	FGameplayTag Message_HealthCrystal;
	FGameplayTag Message_HealthPotion;
	FGameplayTag Message_ManaCrystal;
	FGameplayTag Message_ManaPotion;

	FGameplayTag Input_Primary;
	FGameplayTag Input_Secondary;
	FGameplayTag Input_1;
	FGameplayTag Input_2;
	FGameplayTag Input_3;
	FGameplayTag Input_4;
	FGameplayTag Input_Passive_1;
	FGameplayTag Input_Passive_2;


	FGameplayTag Effects_HitReact;

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;
	
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;

	FGameplayTag Abilities_HitReact;
	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Eligible;
	FGameplayTag Abilities_Status_Unlocked;
	FGameplayTag Abilities_Status_Equipped;

	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;

	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Cooldown_Fire_FireBolt;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	TMap<FGameplayTag, FGameplayTag> DamageTypeToResistances;

protected:
private:
	static FAuraGameplayTags GameplayTags;
};
