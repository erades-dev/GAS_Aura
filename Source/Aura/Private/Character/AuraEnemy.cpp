// Erades

#include "Character/AuraEnemy.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AuraGameplayTags.h"
#include "Aura/Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UI/Widget/AuraUserWidget.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->CustomDepthStencilValue = CUSTOM_DEPTH_RED;
	Weapon->CustomDepthStencilValue = CUSTOM_DEPTH_RED;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return (CharacterLevel);
}

void AAuraEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AAuraEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority())
		return;

	AuraAIController = Cast<AAuraAIController>(NewController);
	AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AuraAIController->RunBehaviorTree(BehaviorTree);

	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);

}

void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
{
	bHitReaction = (NewCount > 0);
	if (bHitReaction)
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), true);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	}
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	check(AbilitySystemComponent);
	InitAbilityActorInfo();
	InitializeBindings();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
		UAuraAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, CharacterLevel, AbilitySystemComponent);
}

void AAuraEnemy::InitializeBindings()
{
	UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject());
	if (AuraUserWidget)
	{
		AuraUserWidget->SetWidgetController(this);
	}

	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(GetAttributeSet());
	if (AuraAS)
	{
		// TODO: Not sure what "const FOnAttributeChangeData& Data" means. I think it works capturing AuraAS.GetHealth()

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
		});
		OnHealthChanged.Broadcast(AuraAS->GetHealth());

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());

		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AAuraEnemy::HitReactTagChanged);
	}
}
