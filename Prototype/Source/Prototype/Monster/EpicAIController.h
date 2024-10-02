// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EpicAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AEpicAIController : public AAIController
{
	GENERATED_BODY()

public:

	AEpicAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;


private:
	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;


	
};
