// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Animation/BaseAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */


UCLASS()
class PROTOTYPE_API UPlayerAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void JumpToSection(int32 sectionIndex);
	virtual void PlayAttackMontage();
	
	AttackDelegate _attackDelegate;
	DeathDelegate _deathDelegate_Knight;

	UFUNCTION()
	virtual void AnimNotify_Attackhit();

	UFUNCTION()
	virtual void AnimNotify_Death();

};
