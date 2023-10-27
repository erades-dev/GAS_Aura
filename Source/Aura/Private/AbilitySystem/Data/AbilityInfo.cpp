// Erades

#include "AbilitySystem/Data/AbilityInfo.h"

#include "AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoByTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (FAuraAbilityInfo Info : AbilityInfo)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return (Info);
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	return (FAuraAbilityInfo());
}
