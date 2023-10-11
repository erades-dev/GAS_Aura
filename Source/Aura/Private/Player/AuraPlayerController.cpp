// Erades

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
	: LastActor(nullptr), ThisActor(nullptr) {
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(const float DeltaTime) {
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace() {
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (CursorHit.bBlockingHit) {
		LastActor = ThisActor;
		ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

		/**
		 * A.LastActor is null&& ThisActor is null
		 *		- Do Nothing.
		 * B. LastActor is null && ThisActor is valid.
		 *		- Hilight ThisActor.
		 * C. LastActor is valitr && ThisActor is null.
		 *		- Unhilight LastActor.
		 * D. Both actors are valid and diferent.
		 *		- Unhilight LastActor and Hilight ThisActor.
		 * E. Both actors are valid and equal.
		 *		- Do nothing.
		 */

		if (!LastActor) {
			if (ThisActor) {
				ThisActor->HighlightActor();
			}
		}
		else {
			if (!ThisActor) {
				LastActor->UnHighlightActor();
			}
			else {
				if (LastActor != ThisActor) {
					LastActor->UnHighlightActor();
					ThisActor->HighlightActor();
				}
			}
		}
	}
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) {
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue &InputActionValue) {
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn *ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
