// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/Monster.h"
#include "Monster.h"
#include "BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ABossMonster : public AMonster
{
	GENERATED_BODY() 
	
public:
	// Sets default values for this character's properties
	ABossMonster();

	bool PerformGimmick();
	void JumpAttack(FVector TargetLocation);
	bool GetIsDashing(){return IsDashing;}
	bool GetIsJumping(){return IsJumping;}
	virtual void Landed(const FHitResult& Hit) override;

	void Dash(FVector TargetLocation);
	void DashEnd();
	void UpdateDash();

	void DestroyObstacle();


	//void SpawnObstacles();
	
	//void CheckGimmickResult();

	//virtual void Jump() override;

	//void OnRushCompleted();


private:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Attack_AI() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class AMyDecal> _decal;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Obstacle", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABossObstacle> _obstacle;

	TArray<ABossObstacle*> SpawnedObstacles; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UMonster_Boss01_AnimInstance* _bossMonster01_AnimInstance;

	int32 ObstacleDestroyCount;

	bool IsJumping = false;
	bool IsDashing = false;

	float JumpStartTime; 
    float JumpDuration;

	FVector DashEndLocation;
	float DashDistance = 2000.0f;
    float DashSpeed = 2000.0f; 
	FVector DashDirection;
  
};
