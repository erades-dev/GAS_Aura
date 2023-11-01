// Erades

#include "AuraAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilityTypes.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return (*AuraAssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraDamagePairing::InitializePairingInfo();

	// This is required to use Target Data.
	UAbilitySystemGlobals::Get().InitGlobalData();
}
