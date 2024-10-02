// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Creature.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACreature::ACreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACreature::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACreature::Init()
{
}

void ACreature::Disable()
{
}

void ACreature::AttackHit()
{
	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 50.0f;

	bool bResult = GetWorld()->SweepMultiByChannel(
		hitResults,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;

	FColor drawColor = FColor::Green;
	

	if (bResult)
	{
		drawColor = FColor::Red;

		for (auto &hitResult : hitResults)
		{
			if (hitResult.GetActor() && hitResult.GetActor()->IsValidLowLevel())
			{
				FDamageEvent DamageEvent;
				//hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), DamageEvent, GetController(), this);
			}
		}
	}
	DrawDebugSphere(GetWorld(), center, attackRadius, 32, drawColor, false, 0.3f);

}

float ACreature::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	return 0.0f;
}
