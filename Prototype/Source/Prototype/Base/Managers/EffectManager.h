// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "EffectManager.generated.h"

class AParticleEffect;

UCLASS()
class PROTOTYPE_API AEffectManager : public AActor
{
	GENERATED_BODY()
	
public:	

	AEffectManager();

	void CreateNiagaraClass(FString name, FString path);
	void CreateEffect();
	void Play(FString name, FVector location, FRotator rotator = FRotator::ZeroRotator);

	virtual void Tick(float DeltaTime) override;


public:

	// 나이아가라 시스템을 키-값으로 관리하는 TMap
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TMap<FString, UNiagaraSystem*> NiagaraEffects;

	// 특정 Skeletal Mesh에 이펙트를 Attach하여 재생
	UNiagaraComponent* PlayAttachedEffect(const FString& Key, USceneComponent* AttachToComponent, FName AttachPointName = NAME_None);


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
