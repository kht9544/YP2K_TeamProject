// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticleEffect.generated.h"

UCLASS()
class PROTOTYPE_API AParticleEffect : public AActor
{
	GENERATED_BODY()
	
public:	

	AParticleEffect();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void Play(FVector location, FRotator rotator);
	bool IsPlaying();

private:
	
	
	UFUNCTION()
	void End(UNiagaraComponent* niagaraComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* _niagaraCom;
	

};
