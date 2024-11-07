// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Managers/EffectManager.h"

#include "Components/SceneComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "VFX/ParticleEffect.h"



AEffectManager::AEffectManager()
{
	PrimaryActorTick.bCanEverTick = false;

	_rootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = _rootComponent;
	
	//Player : Skill 2 Meteor Niagara
	CreateNiagaraClass(TEXT("NS_Meteor"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/NS_Meteor_BP.NS_Meteor_BP_C'"));
	
	//Player : AttakHit Particle
	CreateNiagaraClass(TEXT("P_Greystone_Novaborn_Primary_Impact"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Particle/P_PlayerAttackHit_BP.P_PlayerAttackHit_BP_C'"));

	//Plaer : Skill 3 FireBall Niagara
	CreateNiagaraClass(TEXT("NS_Projectile_01"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_FireBall_BP.NS_FireBall_BP_C'"));
	CreateNiagaraClass(TEXT("NS_Projectile_01_Hit"), TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Niagara/NS_FireBallHit_BP.NS_FireBallHit_BP_C'"));
}

void AEffectManager::CreateNiagaraClass(FString name, FString path)
{
	//ConstructorHelpers::FClassFinder<UNiagaraSystem> effect(*path);
	ConstructorHelpers::FClassFinder<AParticleEffect> effect(*path);
	if (effect.Succeeded())
	{
		_classTable.Add(name, effect.Class);
	}

}

void AEffectManager::CreateEffect()
{
	for (auto classPair : _classTable)
	{
		FString name = classPair.Key;
		_effectTable.Add(name);

		for (int32 i = 0; i < _poolCount; i++)
		{
			FString tempName = name + FString::FromInt(i);
			FActorSpawnParameters params;
			params.Name = FName(*tempName);
			auto effect = GetWorld()->SpawnActor<AParticleEffect>(classPair.Value, FVector::ZeroVector, FRotator::ZeroRotator, params);

			effect->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			_effectTable[name].Add(effect);
		}
	}
}

void AEffectManager::Play(FString name, FVector location, FRotator rotator)
{

	if (!_effectTable.Contains(name))
		return;

	auto findEffect = _effectTable[name].FindByPredicate(
		[](AParticleEffect* effect)-> bool
		{
			return !effect->IsPlaying();
		});

	if (findEffect)
		(*findEffect)->Play(location, rotator);


}


void AEffectManager::BeginPlay()
{
	Super::BeginPlay();
	
	CreateEffect();
}


void AEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


