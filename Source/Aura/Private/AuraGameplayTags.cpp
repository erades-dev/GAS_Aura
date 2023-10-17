// Erades

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{

	// Primary.
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"), FString("Reduce damage taken, improves block chance"));

	// Secondary.
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), FString("Reduce damage taken, improves block chance"));

	// Transient.
	GameplayTags.Attributes_Transient_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Transient.Health"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Attributes_Transient_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Transient.Mana"), FString("Reduce damage taken, improves block chance"));

	// Message
	GameplayTags.Message_HealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Message.HealthCrystal"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Message_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Message.HealthPotion"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Message_ManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Message.ManaCrystal"), FString("Reduce damage taken, improves block chance"));

	GameplayTags.Message_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Message.ManaPotion"), FString("Reduce damage taken, improves block chance"));

	// Input

	GameplayTags.Input_Primary = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Primary"), FString(""));

	GameplayTags.Input_Secondary = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Secondary"), FString(""));

	GameplayTags.Input_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.1"), FString(""));

	GameplayTags.Input_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.2"), FString(""));

	GameplayTags.Input_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.3"), FString(""));

	GameplayTags.Input_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.4"), FString(""));
}