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
	
public:

	AEpicMonster_witch();

	void MagicShot();
	void SumonedMonster();
	void testDecalSkill();
	void MeleeAttackhit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual void Attack_AI() override;



private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEpicProjectile> _projectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sumonedmonster, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ANormalMonster> _SumonedMonster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMagicDecal> _tedecal;
};
