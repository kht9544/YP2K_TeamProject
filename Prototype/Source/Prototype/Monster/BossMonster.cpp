// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BossMonster.h"
#include "../Player/MyPlayer.h"
#include "../Animation/Monster_Boss01_AnimInstance.h"
#include "../Player/Creature.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Base/MyGameInstance.h"
#include "../Base/Managers/SoundManager.h"


ABossMonster::ABossMonster()
{
    PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM( TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster_01.BossMonster_01'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
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

		 // 사운드 매니저를 사용해 사운드 출력
		if (SoundManager && !soundKey.IsEmpty())
		{
			// 타이머를 사용하여 사운드를 지연 재생
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, soundKey]()
				{
					UE_LOG(LogTemp, Warning, TEXT("Playing sound key: %s"), *soundKey);
					SoundManager->PlaySound(soundKey, GetActorLocation());
				}, 0.1f, false);  // 0.1초 후 사운드 재생
		}


	}

}

bool ABossMonster::PerformGimmick()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGimmick"));

    

    return false;
}




