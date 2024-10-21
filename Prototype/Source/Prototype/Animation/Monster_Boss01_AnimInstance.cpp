// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Monster_Boss01_AnimInstance.h"

UMonster_Boss01_AnimInstance::UMonster_Boss01_AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BM_01
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster01_AnimMontage.BossMonster01_AnimMontage'"));

	if (BM_01.Succeeded())
	{
		_myAnimMontage = BM_01.Object;
	}
}

void UMonster_Boss01_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonster_Boss01_AnimInstance::PlayAttackMontage()
{
	Super::PlayAttackMontage();
}

void UMonster_Boss01_AnimInstance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}

void UMonster_Boss01_AnimInstance::AnimNotify_Attackhit()
{
	_attackDelegate.Broadcast();
}

void UMonster_Boss01_AnimInstance::AnimNotify_Death()
{
	_deathDelegate.Broadcast();
}

