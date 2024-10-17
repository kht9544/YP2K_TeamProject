// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/BossMonster.h"
#include "../Player/MeteorDecal.h"

ABossMonster::ABossMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_07/mesh/SK_SKnight_07_full.SK_SKnight_07_full'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<AMeteorDecal> MD(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/GimmicMeteorDecal_BP.GimmicMeteorDecal_BP_C'"));
	if (MD.Succeeded())
	{
		_decal = MD.Class;
	}
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ABossMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (_StatCom)
	{
		_StatCom->SetBossLevelInit(1);
	}
}

bool ABossMonster::PerformGimmick()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);

	for (int i = 0; i < 20; i++)
	{
		float RandomX = FMath::RandRange(-1000.0f, 1000.0f);
		float RandomY = FMath::RandRange(-1000.0f, 1000.0f);

		FVector MeteorStartLocation = GetActorLocation() + FVector(RandomX, RandomY, 5000.0f);

		FVector DecalLocation = GetActorLocation() + FVector(RandomX, RandomY, 0.0f); 

        DecalLocation.Z -= 98.0f;

		AMeteorDecal *MeteorDecal = GetWorld()->SpawnActor<AMeteorDecal>(_decal, DecalLocation, FRotator::ZeroRotator, SpawnParams);
		if (MeteorDecal)
		{
			MeteorDecal->StartMeteor(MeteorStartLocation, DecalLocation, 3.0f);
		}
	}

	SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);

	return false;
}
