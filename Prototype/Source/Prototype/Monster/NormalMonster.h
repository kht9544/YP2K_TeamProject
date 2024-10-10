// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.h"
#include "NormalMonster.generated.h"

UCLASS()
class PROTOTYPE_API ANormalMonster : public AMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANormalMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

};
