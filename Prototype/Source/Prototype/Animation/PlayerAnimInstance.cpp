// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "../Player/MyPlayer.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	_isFalling = false;
	_isDead = false;

    _speed = 0.0f;
	_Direction = 0;
	_vertical = 0;
	_horizontal = 0;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
   /* Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();*/

	AMyPlayer* myCharacter = Cast<AMyPlayer>(TryGetPawnOwner());

	if (myCharacter != nullptr)
	{
		_speed = myCharacter->GetVelocity().Size();

		_isFalling = myCharacter->GetMovementComponent()->IsFalling();
		_Direction = CalculateDirection(myCharacter->GetVelocity(), myCharacter->GetActorRotation());

		_vertical = _speed + (myCharacter->GetVertical() - _speed) * (DeltaSeconds);
		_horizontal = _Direction + (myCharacter->GetHorizontal() - _Direction) * (DeltaSeconds);
		//_isDead = (myCharacter->GetCurHp() <= 0);

		_vertical = _vertical + (myCharacter->GetVertical() - _vertical) * (DeltaSeconds);

	}
}

void UPlayerAnimInstance::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_myAnimMontage))
	{
		Montage_Play(_myAnimMontage);
	}
}
