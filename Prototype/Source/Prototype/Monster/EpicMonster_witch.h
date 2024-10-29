// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/Monster.h"
#include "GameFramework/Character.h"

#include "EpicMonster_witch.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AEpicMonster_witch : public AMonster
{
	GENERATED_BODY()
	
	AEpicMonster_witch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void MeleeAttackhit();

	void RangedAttackhit();

	//test shoot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEpicProjectile> _projectileClass;

	void testShot();

	void SumonedMonster();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sumonedmonster, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ANormalMonster> _SumonedMonster;
};
