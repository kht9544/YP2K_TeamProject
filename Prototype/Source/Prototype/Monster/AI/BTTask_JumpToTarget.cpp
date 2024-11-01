// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/BTTask_JumpToTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_BossMonster.h"
#include "../BossMonster.h"

UBTTask_JumpToTarget::UBTTask_JumpToTarget()
{
    NodeName = TEXT("Jump");
}

EBTNodeResult::Type UBTTask_JumpToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto boss = Cast<ABossMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (boss == nullptr)
        return EBTNodeResult::Failed;
        
    AActor *TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
    if (TargetActor)
    {
        FVector TargetLocation = TargetActor->GetActorLocation();
        boss->JumpAttack(TargetLocation);
    }
    else
    {
        return EBTNodeResult::Failed;
    }

    return result;
}

void UBTTask_JumpToTarget::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (_isJumping == false)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
