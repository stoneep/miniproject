// Copyright NexonGames


#include "Actor/MiniEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/MiniAttributeSet.h"
#include "Components/SphereComponent.h"


AMiniEffectActor::AMiniEffectActor()
{

	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AMiniEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UMiniAttributeSet* MiniAttributeSet = Cast<UMiniAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UMiniAttributeSet::StaticClass()));

		UMiniAttributeSet* MutableMiniAttributeSet = const_cast<UMiniAttributeSet*>(MiniAttributeSet);
		MutableMiniAttributeSet->SetHealth(MiniAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AMiniEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


void AMiniEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMiniEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMiniEffectActor::EndOverlap);
}


