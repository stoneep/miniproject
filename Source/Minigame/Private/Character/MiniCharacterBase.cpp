// Copyright NexonGames


#include "Character/MiniCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MiniAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "MiniGameplayTags.h"
#include "Minigame/Minigame.h"

AMiniCharacterBase::AMiniCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AMiniCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


UAnimMontage* AMiniCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

// UAnimMontage* AMiniCharacterBase::GetDieReactMontage_Implementation()
// {
// 	return DieReactMontage;
// }

void AMiniCharacterBase::Die()
{
	
	MulticastHandleDeath();
}

void AMiniCharacterBase::MulticastHandleDeath_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();

	bDead = true;
}

void AMiniCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AMiniCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FMiniGameplayTags& GameplayTags = FMiniGameplayTags::Get();
	if(MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if(MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_LeftATK))
	{
		return GetMesh()->GetSocketLocation(LeftATKSocketName);
	}
	if(MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_RightATK))
	{
		return GetMesh()->GetSocketLocation(RightATKSocketName);
	}
	return FVector();
	
	//check(Weapon);
	//return Weapon->GetSocketLocation(WeaponTipSocketName);
}

bool AMiniCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AMiniCharacterBase::GetAvatar_Implementation()
{
	return  this;
}

TArray<FTaggedMontage> AMiniCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

void AMiniCharacterBase::InitAbilityActorInfo()
{
}

void AMiniCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AMiniCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AMiniCharacterBase::AddCharacterAbilities()
{
	UMiniAbilitySystemComponent* MiniASC = CastChecked<UMiniAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	MiniASC->AddCharacterAbilities(StartupAbilities);
}

void AMiniCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
	// if (IsValid(WeaponDissolveMaterialInstance))
	// {
	// 	UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
	// 	Weapon->SetMaterial(0, DynamicMatInst);
	// 	StartWeaponDissolveTimeline(DynamicMatInst);
	// }
}



