// Erades

#include "AbilitySystem/Data/AttributeInfo.h"

#include "AuraLogChannels.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (auto Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return (Info);
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error,
			TEXT("Can't find info for the AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return (FAuraAttributeInfo());
}
