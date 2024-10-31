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
    FVector JumpDirection = (TargetLocation - CurrentLocation).GetSafeNormal();

    float JumpHeight = 500.0f; 
    float Gravity = GetWorld()->GetGravityZ();
    float JumpVelocityZ = FMath::Sqrt(-2 * Gravity * JumpHeight);
    FVector JumpVelocity = JumpDirection * 500.0f;
    JumpVelocity.Z = JumpVelocityZ;


    float HorizontalDistance = (TargetLocation - CurrentLocation).Size2D();
    float TimeToReach = FMath::Sqrt(2 * JumpHeight / -Gravity) + FMath::Sqrt(2 * (CurrentLocation.Z - TargetLocation.Z) / -Gravity);
    float TargetZOffset = TargetLocation.Z - CurrentLocation.Z;

    FVector LandingLocation = TargetLocation;

	LandingLocation.Z-=98.0f;

    LaunchCharacter(JumpVelocity, true, true);

    if (_decal)
    {
        AMyDecal* Decal = GetWorld()->SpawnActor<AMyDecal>(_decal, LandingLocation, FRotator::ZeroRotator);
    }
}


void ABossMonster::Landed(const FHitResult &Hit)
{
	Super::Landed(Hit);

	float LandTime = GetWorld()->GetTimeSeconds();
    JumpDuration = LandTime - JumpStartTime;

    IsJumping = false;

    UE_LOG(LogTemp, Warning, TEXT("Jump Duration: %f seconds"), JumpDuration);

}
