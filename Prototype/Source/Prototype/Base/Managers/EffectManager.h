// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectManager.generated.h"

class AParticleEffect;

UCLASS()
class PROTOTYPE_API AEffectManager : public AActor
{
	GENERATED_BODY()
	
public:	

	AEffectManager();

	void CreateParticle(FString name, FString path);
	void CreateParticleEffects();
	void Play(FString name, FVector location, FRotator rotator = FRotator::ZeroRotator);

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TMap<FString, TSubclassOf<AParticleEffect>> _classTable;
	TMap<FString, TArray<AParticleEffect*>> _effectTable;

	int32 _poolCount = 5;

	UPROPERTY()
	class USceneComponent* _rootComponent;

};
