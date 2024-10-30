// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/BossMonster.h"
#include "../Player/MyPlayer.h"
#include "../Animation/Monster_Boss01_AnimInstance.h"
#include "../Player/Creature.h"
#include "../Player/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "BossObstacle.h"


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
	SpawnObstacles();
	Dash();
	return bGimmickSuccess;
}

void ABossMonster::SpawnObstacles()
{
	if (UWorld *World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		float Distance = 700.0f;
		int32 NumObstacles = 3;

		for (int32 i = 0; i < NumObstacles; ++i)
		{
			float AngleDeg = i * (360.0f / NumObstacles);
			float AngleRad = FMath::DegreesToRadians(AngleDeg);

			FVector Offset = FVector(
				FMath::Cos(AngleRad) * Distance,
				FMath::Sin(AngleRad) * Distance,
				0.0f);

			FVector SpawnLocation = GetActorLocation() + Offset;
			FRotator SpawnRotation = FRotator::ZeroRotator;

			ABossObstacle *Obstacle = World->SpawnActor<ABossObstacle>(_obstacle, SpawnLocation, SpawnRotation, SpawnParams);
			SpawnedObstacles.Add(Obstacle);
		}
	}
}


void ABossMonster::Dash()
{
    if (DashCount >= 5)
    {
        CheckGimmickResult();
        return;
    }

    FVector DashDirection = GetActorForwardVector().GetSafeNormal();
    float DashStrength = 500.0f; 
    
    LaunchCharacter(DashDirection * DashStrength, true, true);

    _bossMonster01_AnimInstance->PlayAttackMontage();

	_bossMonster01_AnimInstance->JumpToSection(1);

	UE_LOG(LogTemp, Warning, TEXT("Dash"));


    for (ABossObstacle* Obstacle : SpawnedObstacles)
    {
        if (Obstacle && FVector::Dist(Obstacle->GetActorLocation(), GetActorLocation()) < 100.0f)
        {
            Obstacle->Destroy();
            DestroyedObstacleCount++;
            SpawnedObstacles.Remove(Obstacle);
            UE_LOG(LogTemp, Warning, TEXT("Obstacle destroyed! Total destroyed: %d"), DestroyedObstacleCount);
            break;
        }
    }

    DashCount++;

    // DashCount가 5 미만인 경우에만 다음 대시 예약
    if (DashCount < 5)
    {
        FTimerHandle UnusedHandle;
        GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &ABossMonster::Dash, 3.5f, false);  // 0.5초마다 돌진
    }
}




void ABossMonster::CheckGimmickResult()
{
	UE_LOG(LogTemp, Warning, TEXT("Check"));
	if (DestroyedObstacleCount >= 3)
    {
        bGimmickSuccess = true;
        UE_LOG(LogTemp, Warning, TEXT("Gimmick succeeded!"));
    }
    else
    {
        bGimmickSuccess = false;
        UE_LOG(LogTemp, Warning, TEXT("Gimmick failed, restoring health to max."));
        _StatCom->SetHp(_StatCom->GetMaxHp());
    }

    DashCount = 0;
    DestroyedObstacleCount = 0;
    SpawnedObstacles.Empty();
}



void ABossMonster::Jump()
{
	Super::Jump();

	UE_LOG(LogTemp, Warning, TEXT("Jump"));
    FVector ForwardVector = GetActorForwardVector();
    
	FVector JumpForwardForce = {500.f,0.f, 500.f};

    LaunchCharacter(ForwardVector * JumpForwardForce, true, true);
}

void ABossMonster::OnRushCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("Rush Completed"));
	
    return;
}
