// Erades

#include "Actor/AuraEffectActor.h"
#include <Components/SphereComponent.h>
#include <AbilitySystemInterface.h>
#include "abilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor() {
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Mesh);
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtheComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	IAbilitySystemInterface *Interface = Cast<IAbilitySystemInterface>(OtherActor);
	if (Interface) {
		const UAttributeSet *AttributeSet = Interface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass());
		const UAuraAttributeSet *AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
		// TODO: Change to apply Gameplay Effect. For now using const _cast as hack.
		UAuraAttributeSet *MutableAuraAttributeSet = const_cast<UAuraAttributeSet *>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 15.0f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex) {
}

void AAuraEffectActor::BeginPlay() {
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}
