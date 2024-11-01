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

	_niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	RootComponent = _niagaraCom;

}


void AParticleEffect::BeginPlay()
{
	Super::BeginPlay();

	//_particleCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::End);
	//End(_particleCom);

	_niagaraCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::End);
	End(_niagaraCom);
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
	return _niagaraCom->IsActive();
}

void AParticleEffect::End(UNiagaraComponent* niagaraComponent)
{
	if (niagaraComponent)
		niagaraComponent->Deactivate();
}

