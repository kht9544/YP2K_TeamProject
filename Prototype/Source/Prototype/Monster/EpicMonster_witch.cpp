// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/EpicMonster_witch.h"
#include "Base/MyGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Monster/AI/AIController_Epic.h"

#include "Engine/DamageEvents.h"

#include "EpicProjectile.h"
#include "../Animation/Monster_N_AnimInstance.h"

#include "NormalMonster.h"

AEpicMonster_witch::AEpicMonster_witch()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> witch
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMorigesh/Characters/Heroes/Morigesh/Meshes/Morigesh.Morigesh'"));

	if (witch.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(witch.Object);
	}


	AIControllerClass = AAIController_Epic::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEpicMonster_witch::BeginPlay()
{
	Super::BeginPlay();

}

void AEpicMonster_witch::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_StatCom)
	{
		_StatCom->SetEpicLevelInit(1);
	}

	auto _monster_N_AnimInstance = Cast<UMonster_N_AnimInstance>(GetMesh()->GetAnimInstance());
	if (_monster_N_AnimInstance->IsValidLowLevelFast())
	{
		_monster_N_AnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackEnded);
		_monster_N_AnimInstance->_attackDelegate.AddUObject(this, &AEpicMonster_witch::testShot);
		_monster_N_AnimInstance->_deathDelegate.AddUObject(this, &AMonster::Disable);
	}
}

void AEpicMonster_witch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEpicMonster_witch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEpicMonster_witch::MeleeAttackhit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 150.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;

	FColor drawColor = FColor::Green;


	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		FDamageEvent DamageEvent;
		//hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), DamageEvent, GetController(), this);

	}

	DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor, false, 2.0f);
}

void AEpicMonster_witch::RangedAttackhit()
{
	FName MouthSocketName = TEXT("mouth");


	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 1000.0f;
	float attackRadius = 20.0f;

	FVector forward = GetActorForwardVector();
	FQuat quat = FQuat::FindBetweenVectors(FVector(0, 0, 1), forward); // FRotationMatrix::MakeFromZ(forward).ToQuat();

	FVector start = GetMesh()->GetSocketLocation(MouthSocketName);
	FVector end = start + forward * attackRange;
	FVector center = (start + end) * 0.5f;
	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		start,
		end,
		quat,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);



	FColor drawColor = FColor::Green;

	// Check if a hit was detected and apply damage if valid
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		FDamageEvent damageEvent;
		FVector hitPoint = hitResult.ImpactPoint;
		_hitPoint = hitResult.ImpactPoint;
		//testShot();

	}


	// DEBUG : DrawCapsule
	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5f, attackRadius, quat, drawColor, false, 2.0f);
}

void AEpicMonster_witch::testShot()
{
}

void AEpicMonster_witch::SumonedMonster()
{
	if (_SumonedMonster != nullptr)
	{
		for (int i = 0; i < 2; ++i)
		{
			FVector SpawLocation = GetActorLocation() + FMath::VRand() * 200.0f;
			FRotator SpawRotation = FRotator::ZeroRotator;

			GetWorld()->SpawnActor<ANormalMonster>(_SumonedMonster, SpawLocation, SpawRotation);
		}
	}
}
