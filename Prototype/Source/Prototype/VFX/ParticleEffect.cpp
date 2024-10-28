// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/ParticleEffect.h"

#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


AParticleEffect::AParticleEffect()
{
	PrimaryActorTick.bCanEverTick = false;

	_particleCom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = _particleCom;

	_niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	//RootComponent = _niagaraCom;
	_niagaraCom->SetupAttachment(RootComponent);
	//_niagaraCom->SetupAttachment(RootComponent);

}


void AParticleEffect::BeginPlay()
{
	Super::BeginPlay();

	_particleCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::End);
	End(_particleCom);

	_niagaraCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::EndNiagara);
	EndNiagara(_niagaraCom);
}


void AParticleEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParticleEffect::Play(FVector location, FRotator rotator)
{
	if (_niagaraCom->IsActive())
		return;

	SetActorLocationAndRotation(location, rotator);
	_niagaraCom->ActivateSystem();
}

bool AParticleEffect::IsPlaying()
{
	if (_niagaraCom->IsActive())
		return true;
	return false;
}

void AParticleEffect::End(UParticleSystemComponent* particle)
{
	if (particle)
		particle->DeactivateSystem();
}

void AParticleEffect::EndNiagara(UNiagaraComponent* particle)
{
	//if (particle)
	//{
	//	particle->Deactivate();
	//	particle->DestroyComponent();
	//}

	if (particle && _niagaraCom)
	{
		particle->Deactivate();
		particle->DestroyComponent();
	}

}


