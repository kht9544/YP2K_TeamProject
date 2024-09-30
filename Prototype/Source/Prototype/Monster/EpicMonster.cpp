// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/EpicMonster.h"
#include "../Player/MyPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEpicMonster::AEpicMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Griffon
	(TEXT("/Script/Engine.SkeletalMesh'/Game/QuadrapedCreatures/Griffon/Meshes/SK_Griffon.SK_Griffon'"));

	if (Griffon.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Griffon.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_capsuleComponent = GetCapsuleComponent();
	_capsuleComponent->InitCapsuleSize(250.0f, 250.0f); 


}

void AEpicMonster::BeginPlay()
{
	Super::BeginPlay();

}

void AEpicMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AEpicMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEpicMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
