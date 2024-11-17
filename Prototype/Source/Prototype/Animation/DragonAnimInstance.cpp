// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DragonAnimInstance.h"

UDragonAnimInstance::UDragonAnimInstance()
{

}

void UDragonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);



}

void UDragonAnimInstance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}

void UDragonAnimInstance::AnimNotify_Death()
{
	_deathDelegate_Dragon.Broadcast();
}
