// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/BossMonster.h"
#include "../Player/MyPlayer.h"
#include "../Animation/Monster_Boss01_AnimInstance.h"
#include "../Player/Creature.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "BossObstacle.h"
#include "GameFramework/CharacterMovementComponent.h"

ABossMonster::ABossMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster_01.BossMonster_01'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<ABossObstacle> BO(
		TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/BossMonster/Obstacle_BP.Obstacle_BP_C'"));
	if (BO.Succeeded())
	{
		_obstacle = BO.Class;
	}

	DashSpeed = 12000.f;
	DashDuration = 2.0f;
	bIsDashing = false;
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ABossMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (_StatCom)
	{
		_StatCom->SetBossLevelInit(1);
	}

	_bossMonster01_AnimInstance = Cast<UMonster_Boss01_AnimInstance>(GetMesh()->GetAnimInstance());
	if (_bossMonster01_AnimInstance->IsValidLowLevelFast())
	{
		_bossMonster01_AnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackEnded);
		_bossMonster01_AnimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_bossMonster01_AnimInstance->_deathDelegate.AddUObject(this, &AMonster::Disable);
	}
}

void ABossMonster::Attack_AI()
{

	if (_isAttacking == false && _bossMonster01_AnimInstance != nullptr)
	{
		_bossMonster01_AnimInstance->PlayAttackMontage();
		_isAttacking = true;

		int32 RandomSectionIndex = FMath::RandRange(1, 3);

		_bossMonster01_AnimInstance->JumpToSection(RandomSectionIndex);
	}
}

bool ABossMonster::PerformGimmick()
{
	if (UWorld *World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		float DistanceFromBoss = 700.0f;
		int32 NumObstacles = 3;

		for (int32 i = 0; i < NumObstacles; ++i)
		{
			float AngleDeg = i * (360.0f / NumObstacles);
			float AngleRad = FMath::DegreesToRadians(AngleDeg);

			FVector Offset = FVector(
				FMath::Cos(AngleRad) * DistanceFromBoss,
				FMath::Sin(AngleRad) * DistanceFromBoss,
				0.0f);

			FVector SpawnLocation = GetActorLocation() + Offset;
			FRotator SpawnRotation = FRotator::ZeroRotator;

			ABossObstacle *Obstacle = World->SpawnActor<ABossObstacle>(_obstacle, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}

	return false;
}

void ABossMonster::Rush()
{
	
}

