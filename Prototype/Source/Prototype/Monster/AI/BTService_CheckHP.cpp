// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/BTService_CheckHP.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController_BossMonster.h"
#include "../Monster.h"
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

    AMonster *ControlledPawn = Cast<AMonster>(AIController->GetPawn());

    if (ControlledPawn)
    {

        float CurrentHealthPercent = (ControlledPawn->_StatCom->HpRatio())*100.f;
        float hp = ControlledPawn->_StatCom->GetCurHp();
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat("BossHealth", CurrentHealthPercent);
        UE_LOG(LogTemp, Warning, TEXT("curhp:%f"), hp);
        UE_LOG(LogTemp, Warning, TEXT("hp:%f"), CurrentHealthPercent);

        if (CurrentHealthPercent <= 70.0f && !OwnerComp.GetBlackboardComponent()->GetValueAsBool("GimmickExecuted"))
        {
            bool bGimmickSuccess = ControlledPawn->PerformGimmick();

            if (bGimmickSuccess)
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsBool("GimmickExecuted", true);
            }
            else
            {
               //ControlledPawn->_StatCom->Heal(30.f); // 체력 30% 회복
                OwnerComp.GetBlackboardComponent()->SetValueAsBool("GimmickExecuted", false);
            }
        }

        if (CurrentHealthPercent <= 50.0f && !OwnerComp.GetBlackboardComponent()->GetValueAsBool("Phase2"))
        {
            UE_LOG(LogTemp, Warning, TEXT("Phase2"));
            OwnerComp.GetBlackboardComponent()->SetValueAsBool("Phase2", true);
        }

        if (CurrentHealthPercent < 10.0f && !OwnerComp.GetBlackboardComponent()->GetValueAsBool("Phase3"))
        {
            UE_LOG(LogTemp, Warning, TEXT("Phase3"));
            OwnerComp.GetBlackboardComponent()->SetValueAsBool("Phase2", false);
            OwnerComp.GetBlackboardComponent()->SetValueAsBool("Phase3", true);
        }
    }
}

