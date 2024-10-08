// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "../Player/MyPlayer.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Knignt
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Knight_Montage.Knight_Montage'"));

	if (Knignt.Succeeded())
	{
		_myAnimMontage = Knignt.Object;
	}

	
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//AMyPlayer* myCharacter = Cast<AMyPlayer>(TryGetPawnOwner());

}

void UPlayerAnimInstance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Super::PlayAttackMontage();
}

void UPlayerAnimInstance::AnimNotify_Attackhit()
{
	_attackDelegate.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_Death()
{
	_deathDelegate_Knight.Broadcast();
}
