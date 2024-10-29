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

	void Rush(); 

	void SetCanTeleport(bool CanTel){_CanTeleport = CanTel;}
	
	bool bIsDashing;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Attack_AI() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class AMyDecal> _decal;

	FTimerHandle DashTimerHandle;

	bool _CanTeleport = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Obstacle", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABossObstacle> _obstacle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UMonster_Boss01_AnimInstance* _bossMonster01_AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash",meta = (AllowPrivateAccess = "true"))
    float DashSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash",meta = (AllowPrivateAccess = "true"))
    float DashDuration;

    TArray<ABossObstacle*> SpawnedObstacles; 

    int32 RemainingRushes = 5; 

   


};
