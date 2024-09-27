// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/PlayerAnimInstance.h"
#include "Knight_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UKnight_AnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	UKnight_AnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void JumpToSection(int32 sectionIndex) override;


};
