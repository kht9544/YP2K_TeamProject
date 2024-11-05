// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Monster_Epic01_Anim.h"

UMonster_Epic01_Anim::UMonster_Epic01_Anim()
{

	// 근접공격 몽타주
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Monster_Epic_01_AttackNear
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/EpicMonster/EpicMonster01_AnimMontage_Near.EpicMonster01_AnimMontage_Near'"));

	if (Monster_Epic_01_AttackNear.Succeeded())
	{
		_myAnimMontage = Monster_Epic_01_AttackNear.Object;
	}

	// 원거리공격 몽타주
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Monster_Epic_01_AttackFar
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/EpicMonster/EpicMonster01_AnimMontage_Far.EpicMonster01_AnimMontage_Far'"));


	// 도트마법 몽타주
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Monster_Epic_01_Magic
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/EpicMonster/EpicMonster01_AnimMontage_Far2.EpicMonster01_AnimMontage_Far2'"));



}
