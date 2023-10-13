// Erades

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "../Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 *
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface {
	GENERATED_BODY()

public:
	AAuraEnemy();

	// begin Enemy Interface.
	void HighlightActor() override;
	void UnHighlightActor() override;
	// end Enemy Interface.

protected:
	virtual void BeginPlay() override;

private:
	virtual void InitAbilityActorInfo() override;
};
