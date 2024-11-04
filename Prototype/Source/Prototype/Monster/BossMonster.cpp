// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/BossMonster.h"
#include "../Player/MyPlayer.h"
#include "../Animation/Monster_Boss01_AnimInstance.h"
#include "../Player/Creature.h"
#include "../Player/MyDecal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Base/MyGameInstance.h"
#include "../Base/Managers/SoundManager.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

ABossMonster::ABossMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster_01.BossMonster_01'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<AMyDecal> MD(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/BasicDecal_BP.BasicDecal_BP_C'"));
	if (MD.Succeeded())
	{
		_decal = MD.Class;
	}

	_exp = 1;
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
		_isAttacking = true;
		int32 RandomSectionIndex = FMath::RandRange(1, 3);
		UE_LOG(LogTemp, Warning, TEXT("Selected RandomSectionIndex: %d"), RandomSectionIndex);

		_bossMonster01_AnimInstance->PlayAttackMontage();
		_bossMonster01_AnimInstance->JumpToSection(RandomSectionIndex);

		FString soundKey;
		if (RandomSectionIndex == 1)
		{
			soundKey = "BossMonsterAttack_Hard";
		}
		else if (RandomSectionIndex == 2)
		{
			soundKey = "BossMonsterPunch";
		}
		else if (RandomSectionIndex == 3)
		{
			soundKey = "BossMonsterPunch";
		}

		if (SoundManager && !soundKey.IsEmpty())
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, soundKey]()
												   {
					UE_LOG(LogTemp, Warning, TEXT("Playing sound key: %s"), *soundKey);
					SoundManager->PlaySound(soundKey, GetActorLocation()); }, 0.1f, false);
		}
	}
}

float ABossMonster::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	UBaseAnimInstance *AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayHitReactionMontage();
	}

	SoundManager->PlaySound(*GetGuardOff(), _hitPoint);

	if(ObstacleDestroyCount >=5)
	{
		_StatCom->AddCurHp(-Damage);
	}
	else
	{
		_StatCom->AddCurHp(-Damage/(5-ObstacleDestroyCount));
	}


	if (_StatCom->IsDead())
	{
		SoundManager->PlaySound(*GetDeadSoundName(), _hitPoint);

		SetActorEnableCollision(false);
		auto controller = GetController();
		if (controller)
			GetController()->UnPossess();
		Destroy();
	}

	return 0.0f;
}



bool ABossMonster::PerformGimmick()
{
	UE_LOG(LogTemp, Warning, TEXT("StartGimmick"));

	return false;
}

void ABossMonster::JumpAttack(FVector TargetLocation)
{
	if (IsJumping)
		return;

	JumpStartTime = GetWorld()->GetTimeSeconds();
	IsJumping = true;

	FVector CurrentLocation = GetActorLocation();
	FVector JumpDirection = (TargetLocation - CurrentLocation).GetSafeNormal2D();
	float HorizontalDistance = FVector::Dist2D(TargetLocation, CurrentLocation);

	float JumpHeight = 500.0f;
	float Gravity = GetWorld()->GetGravityZ();
	float JumpVelocityZ = FMath::Sqrt(-2 * Gravity * JumpHeight);

	float TimeToReach = FMath::Sqrt(2 * JumpHeight / -Gravity) +
						FMath::Sqrt(2 * (CurrentLocation.Z - TargetLocation.Z + JumpHeight) / -Gravity);

	FVector JumpVelocity = JumpDirection * (HorizontalDistance / TimeToReach);
	JumpVelocity.Z = JumpVelocityZ;

	FRotator LookAtRotation = (TargetLocation - CurrentLocation).Rotation();
    SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));

	FVector LandingLocation = TargetLocation;
	LandingLocation.Z -= 98.0f;

	LaunchCharacter(JumpVelocity, true, true);

	if (_decal)
	{
		AMyDecal *Decal = GetWorld()->SpawnActor<AMyDecal>(_decal, LandingLocation, FRotator::ZeroRotator);
	}
}

void ABossMonster::Landed(const FHitResult &Hit)
{
	Super::Landed(Hit);

	float LandTime = GetWorld()->GetTimeSeconds();
	JumpDuration = LandTime - JumpStartTime;
	IsJumping = false;

}



void ABossMonster::Dash(FVector TargetLocation)
{
    if (IsDashing)
        return;
	IsDashing = true;

    FVector StartLocation = GetActorLocation(); 
    DashDirection = (TargetLocation - StartLocation).GetSafeNormal();
    DashDirection.Z = 0.f;

    DashEndLocation = StartLocation + DashDirection * DashDistance;

    FRotator LookAtRotation = DashDirection.Rotation();
    SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));

	FTimerHandle DashTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &ABossMonster::DashEnd, DashDistance / DashSpeed, false);
}

void ABossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDashing)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, DashEndLocation, DeltaTime, DashSpeed);

		FHitResult HitResult;
		SetActorLocation(NewLocation, true, &HitResult);

		if (HitResult.bBlockingHit)
		{
			DashEnd();
			AMyPlayer* Player = Cast<AMyPlayer>(HitResult.GetActor());
			if(Player!=nullptr)
			{
				if (_bossMonster01_AnimInstance)
                {
                    _bossMonster01_AnimInstance->PlayUpAttackMontage();
                }
				FVector ThrowDirection = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
				ThrowDirection.Z = 1.f;
                FVector ThrowForce = ThrowDirection * 1000.0f;
                Player->LaunchCharacter(ThrowForce, true, true);
			}
		}
		else if (FVector::DistSquared(NewLocation, DashEndLocation) <= KINDA_SMALL_NUMBER)
		{
			DashEnd();
		}
	}
}



void ABossMonster::DashEnd()
{
    IsDashing = false;

    GetCharacterMovement()->StopMovementImmediately();
}

