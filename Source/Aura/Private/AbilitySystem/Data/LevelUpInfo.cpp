// Erades

#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXp(const float Xp) const
{
	int32 LevelReach = 1;
	const int32 MaxLevel = LevelUpInformation.Num();
	while (LevelUpInformation[LevelReach].Xp < Xp)
	{
		LevelReach++;
		if (LevelReach >= MaxLevel)
		{
			return (MaxLevel);
		}
	}
	return (LevelReach);
}
