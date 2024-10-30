// Fill out your copyright notice in the Description page of Project Settings.
#include "Monster/AI/BTService_CheckHP.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController_BossMonster.h"
#include "../../Component/StatComponent.h"
#include "../BossMonster.h"
#include "Engine/OverlapResult.h"

UBTService_CheckHP::UBTService_CheckHP()
{
    NodeName = TEXT("Check HPPercent");
}

void UBTService_CheckHP::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto AIController = OwnerComp.GetAIOwner();

    if (AIController == nullptr)
        return;
        
    ABossMonster *boss = Cast<ABossMonster>(AIController->GetPawn());
    if (boss == nullptr || boss->_StatCom == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss or StatComponent is missing."));
        return;
    }

    UStatComponent *stat = boss->_StatCom;
    float HealthPercentage = stat->HpRatio();

    UE_LOG(LogTemp, Warning, TEXT("Boss : HP %f"), HealthPercentage);
    
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat("HpPersent", HealthPercentage);

    bool bGimmickExecuted = OwnerComp.GetBlackboardComponent()->GetValueAsBool("GimmickExecuted");
    if (HealthPercentage < 0.7f && !bGimmickExecuted)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("TriggerGimmick", true);
        bool bGimmickSuccess = boss->PerformGimmick();

        if (bGimmickSuccess)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool("GimmickExecuted", true);
            UE_LOG(LogTemp, Warning, TEXT("Gimmick executed successfully."));
        }
        else
        {
            float MaxHp = stat->GetMaxHp();
            stat->SetHp(MaxHp);
            OwnerComp.GetBlackboardComponent()->SetValueAsBool("GimmickExecuted", false);
            UE_LOG(LogTemp, Warning, TEXT("Gimmick failed, health restored to max."));
        }
    }
    else if (HealthPercentage > 0.7f && bGimmickExecuted)
    {
        // Reset GimmickExecuted if health goes above threshold
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("GimmickExecuted", false);
        UE_LOG(LogTemp, Warning, TEXT("Health above threshold, resetting GimmickExecuted."));
    }
}