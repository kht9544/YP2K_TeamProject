// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{
    _speed = 0.0f;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		_speed = Pawn->GetVelocity().Size();
	}
}
