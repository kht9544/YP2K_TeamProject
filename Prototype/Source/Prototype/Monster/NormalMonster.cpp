// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonster.h"
#include "../Player/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANormalMonster::ANormalMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PS(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton/mesh/SK_Skeleton_base.SK_Skeleton_base'"));

	if (PS.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PS.Object);
	}

	_launchLength = 1000.0f;
}

// Called when the game starts or when spawned
void ANormalMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ANormalMonster::PostInitializeComponents()
{
	 Super::PostInitializeComponents();
}




