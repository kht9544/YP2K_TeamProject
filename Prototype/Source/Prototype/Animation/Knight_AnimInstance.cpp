// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Knight_AnimInstance.h"

UKnight_AnimInstance::UKnight_AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Knignt
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Knight_Montage.Knight_Montage'"));

	if (Knignt.Succeeded())
	{
		_myAnimMontage = Knignt.Object;
	}
}

void UKnight_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UKnight_AnimInstance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}
