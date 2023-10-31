// Erades

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"





UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Intelligence,				"Attributes.Primary.Intelligence",				"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Resilience,				"Attributes.Primary.Resilience",				"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Strength,					"Attributes.Primary.Strength",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Vigor,					"Attributes.Primary.Vigor",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_Armor,					"Attributes.Secondary.Armor",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_ArmorPenetration,		"Attributes.Secondary.ArmorPenetration",		"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_BlockChance,			"Attributes.Secondary.BlockChance",				"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CriticalHitChance,		"Attributes.Secondary.CriticalHitChance",		"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CriticalHitDamage,		"Attributes.Secondary.CriticalHitDamage",		"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CriticalHitResistance,	"Attributes.Secondary.CriticalHitResistance",	"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_HealthRegeneration,		"Attributes.Secondary.HealthRegeneration",		"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_ManaRegeneration,		"Attributes.Secondary.ManaRegeneration",		"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_MaxHealth,				"Attributes.Secondary.MaxHealth",				"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_MaxMana,				"Attributes.Secondary.MaxMana",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Fire,					"Attributes.Resistance.Fire",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Lightning,				"Attributes.Resistance.Lightning",				"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Arcane,				"Attributes.Resistance.Arcane",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Physical,				"Attributes.Resistance.Physical",				"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Transient_Health,					"Attributes.Transient.Health",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Transient_Mana,					"Attributes.Transient.Mana",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Meta_IncomingXp,					"Attributes.Meta.IncomingXp",					"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage,										"Damage",										"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Fire,									"Damage.Fire",									"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Lightning,							"Damage.Lightning",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Arcane,								"Damage.Arcane",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Physical,								"Damage.Physical",								"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Burn,									"Debuff.Burn",									"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Stun,									"Debuff.Stun",									"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Arcane,								"Debuff.Arcane",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Physical,								"Debuff.Physical",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Stat_Chance,							"Debuff.Stat.Chance",							"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Stat_Damage,							"Debuff.Stat.Damage",							"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Stat_Frequency,						"Debuff.Stat.Frequency",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Stat_Duration,						"Debuff.Stat.Duration",							"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Attack,							"Abilities.Attack",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Summon,							"Abilities.Summon",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_HitReact,							"Abilities.HitReact",							"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status,							"Abilities.Status",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Locked,						"Abilities.Status.Locked",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Eligible,					"Abilities.Status.Eligible",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Unlocked,					"Abilities.Status.Unlocked",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Equipped,					"Abilities.Status.Equipped",					"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Type_Offensive,					"Abilities.Type.Offensive",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Type_Passive,						"Abilities.Type.Passive",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Type_None,							"Abilities.Type.None",							"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Fire_FireBolt,						"Abilities.Fire.FireBolt",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Lightning_Electrocute,				"Abilities.Lightning.Electrocute",				"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Cooldown_Fire_FireBolt,						"Cooldown.Fire.FireBolt",						"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_CombatSocket_Weapon,							"CombatSocket.Weapon",							"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_CombatSocket_RightHand,						"CombatSocket.RightHand",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_CombatSocket_LeftHand,						"CombatSocket.LeftHand",						"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effects_HitReact,							"Effects.HitReact",								"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_1,							"Montage.Attack.1",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_2,							"Montage.Attack.2",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_3,							"Montage.Attack.3",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_4,							"Montage.Attack.4",								"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_Primary,								"Input.Primary",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_Secondary,								"Input.Secondary",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_1,										"Input.1",										"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_2,										"Input.2",										"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_3,										"Input.3",										"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_4,										"Input.4",										"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_Passive_1,								"Input.Passive.1",								"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Input_Passive_2,								"Input.Passive.2",								"");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_HealthCrystal,						"Message.HealthCrystal",						"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_HealthPotion,						"Message.HealthPotion",							"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_ManaCrystal,							"Message.ManaCrystal",							"");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_ManaPotion,							"Message.ManaPotion",							"");


FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	// TODO: Keep this class for tags.. Don't we have a GAS globals?
	// Damage Type Array
	GameplayTags.DamageTypeToResistances.Add(TAG_Damage_Fire, TAG_Attributes_Resistance_Fire);
	GameplayTags.DamageTypeToResistances.Add(TAG_Damage_Lightning, TAG_Attributes_Resistance_Lightning);
	GameplayTags.DamageTypeToResistances.Add(TAG_Damage_Arcane, TAG_Attributes_Resistance_Arcane);
	GameplayTags.DamageTypeToResistances.Add(TAG_Damage_Physical, TAG_Attributes_Resistance_Physical);

	GameplayTags.DamageTypeToDebuffs.Add(TAG_Damage_Fire, TAG_Debuff_Burn);
	GameplayTags.DamageTypeToDebuffs.Add(TAG_Damage_Lightning, TAG_Debuff_Stun);
	GameplayTags.DamageTypeToDebuffs.Add(TAG_Damage_Arcane, TAG_Debuff_Arcane);
	GameplayTags.DamageTypeToDebuffs.Add(TAG_Damage_Physical, TAG_Debuff_Physical);
}


	//// Primary.
	//GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Primary.Intelligence"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Primary.Resilience"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Primary.Strength"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Primary.Vigor"), FString("Reduce damage taken, improves block chance"));

	//// Secondary.
	//GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.Armor"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.ArmorPenetration"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.BlockChance"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.CriticalHitChance"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.CriticalHitDamage"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.HealthRegeneration"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.ManaRegeneration"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.MaxHealth"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Secondary.MaxMana"), FString("Reduce damage taken, improves block chance"));

	//// Resistances.
	//GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Resistance.Fire"), FString("Resistance to Fire damage"));

	//GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Resistance.Lightning"), FString("Resistance to Lightning damage"));

	//GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Resistance.Arcane"), FString("Resistance to Arcane damage"));

	//GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Resistance.Physical"), FString("Resistance to Physical damage"));

	//// Transient.
	//GameplayTags.Attributes_Transient_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Transient.Health"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Attributes_Transient_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Transient.Mana"), FString("Reduce damage taken, improves block chance"));

	//// Meta.
	//GameplayTags.Attributes_Meta_IncomingXp = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Attributes.Meta.IncomingXp"), FString("Incoming experience"));

	//// Message.
	//GameplayTags.Message_HealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Message.HealthCrystal"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Message_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Message.HealthPotion"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Message_ManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Message.ManaCrystal"), FString("Reduce damage taken, improves block chance"));

	//GameplayTags.Message_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Message.ManaPotion"), FString("Reduce damage taken, improves block chance"));

	//// Input.
	//GameplayTags.Input_Primary = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.Primary"), FString(""));

	//GameplayTags.Input_Secondary = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.Secondary"), FString(""));

	//GameplayTags.Input_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.1"), FString(""));

	//GameplayTags.Input_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.2"), FString(""));

	//GameplayTags.Input_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.3"), FString(""));

	//GameplayTags.Input_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.4"), FString(""));

	//GameplayTags.Input_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.Passive.1"), FString("Passive"));

	//GameplayTags.Input_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Input.Passive.2"), FString("Passive"));

	//// ...
	//GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Effects.HitReact"), FString("Hit reaction"));

	//GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Damage"), FString("Generic damage type"));

	//GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Damage.Fire"), FString("Fire damage type"));

	//GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Damage.Lightning"), FString("Lightning damage type"));

	//GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Damage.Arcane"), FString("Arcane damage type"));

	//GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Damage.Physical"), FString("Physical damage type"));

	//// Abilities.
	//GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Attack"), FString("Attack ability"));

	//GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Summon"), FString("Summon ability"));

	//GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.HitReact"), FString(""));

	//GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Status.Locked"), FString(""));

	//GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Status.Eligible"), FString(""));

	//GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Status.Unlocked"), FString(""));

	//GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Status.Equipped"), FString(""));

	//GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Type.Offensive "), FString(""));

	//GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Type.Passive"), FString(""));

	//GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Type.None"), FString(""));

	//GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Abilities.Fire.FireBolt"), FString("Firebolt"));

	//// Cooldown.
	//GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Cooldown.Fire.FireBolt"), FString("Cooldown for Firebolt"));

	//// CombatSocket.
	//GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("CombatSocket.Weapon"), FString("Weapon"));

	//GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("CombatSocket.RightHand"), FString("Right Hand"));

	//GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("CombatSocket.LeftHand"), FString("Left hand"));

	//// Montage.
	//GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Montage.Attack.1"), FString("Montage attack 1"));

	//GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Montage.Attack.2"), FString("Montage attack 2"));

	//GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Montage.Attack.3"), FString("Montage attack 3"));

	//GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	//	FName("Montage.Attack.4"), FString("Montage attack 4"));
