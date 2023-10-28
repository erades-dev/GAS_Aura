// Erades

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Xp = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AwardAttributePoint = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 AwardSpellPoint = 1;
};
/**
 * 
 */
UCLASS()
class AURA_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	int32 FindLevelForXp(const float Xp) const;

	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo> LevelUpInformation;
	
};
