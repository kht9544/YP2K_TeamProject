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
		_bossMonster01_AnimInstance->PlayAttackMontage();


		_isAttacking = true;

		int32 RandomSectionIndex = FMath::RandRange(1, 3);

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
			soundKey = "BossMonsterRoar";
		}

		// 사운드 매니저를 사용해 사운드 출력
		if (SoundManager && !soundKey.IsEmpty())
		{
			SoundManager->PlaySound(soundKey, GetActorLocation());
		}



		_bossMonster01_AnimInstance->JumpToSection(RandomSectionIndex);
	}

}

bool ABossMonster::PerformGimmick()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGimmick"));

    

    return false;
}

FString ABossMonster::GetBossMonsterAttack() const
{
	FString soundKey;

	if (UAnimInstance* animInstance = GetMesh()->GetAnimInstance())
	{
		FName currentSection = animInstance->Montage_GetCurrentSection();

		if (currentSection == "Attack1")
		{
			soundKey = "BossMonsterAttack_Hard";
		}
		else if (currentSection == "Attack2")
		{
			soundKey = "BossMonsterPunch";
		}
		else if (currentSection == "Attack3")
		{
			soundKey = "BossMonsterPunch";
		}
	}

	return soundKey;
}



