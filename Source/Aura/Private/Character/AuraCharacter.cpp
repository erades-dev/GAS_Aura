// Erades

#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystemComponent.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerState.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 1100.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Init ability actor info for the server.
	InitAbilityActorInfo();
	InitializeDefaultAttributes();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for the client.
	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetCharacterLevel_Implementation()
{
	const auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return (AuraPlayerState->GetLevel());
}

int32 AAuraCharacter::GetXp_Implementation()
{
	const auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return (AuraPlayerState->GetXp());
}

int32 AAuraCharacter::GetAttributePointsReward_Implementation(const int32 Level) const
{
	const auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return (AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].AwardAttributePoint);
}

int32 AAuraCharacter::GetSpellPointsReward_Implementation(const int32 Level) const
{
	const auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return (AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].AwardSpellPoint);
}

void AAuraCharacter::AddToPLayerLevel_Implementation(int32 InPlayerLevel)
{
	auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToLevel(InPlayerLevel);
}

void AAuraCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	// TODO: add ATTRIBUTES point sto player state.
}

void AAuraCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	// TODO: add SPELL point sto player state.
}

void AAuraCharacter::AddXp_Implementation(const int32 InXp)
{
	auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToXp(InXp);
}

int32 AAuraCharacter::FindLevelForXp_Implementation(const int32 InXp)
{
	const auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	const int32 Level = AuraPlayerState->LevelUpInfo->FindLevelForXp(InXp);
	return (Level);
}

void AAuraCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	auto* AuraPlayerController = Cast<AAuraPlayerController>(GetController());
	if (AuraPlayerController)
	{
		auto* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		if (AuraHUD)
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void AAuraCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = TopDownCameraComponent->GetComponentLocation();
		const FVector NiagaraLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - NiagaraLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}
