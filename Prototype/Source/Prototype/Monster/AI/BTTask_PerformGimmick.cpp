// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTask_PerformGimmick.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController_BossMonster.h"
#include "../BossMonster.h"
#include "../../Component/StatComponent.h"


UBTTask_PerformGimmick::UBTTask_PerformGimmick()
{
    NodeName = TEXT("Perform Gimmick");
}

EBTNodeResult::Type UBTTask_PerformGimmick::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	ABossMonster* Boss = Cast<ABossMonster>(AIController->GetPawn());
	if (!Boss)
		return EBTNodeResult::Failed;

	bool bGimmickSuccess = Boss->PerformGimmick();

	if (bGimmickSuccess)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("GimmickExecuted", true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("Phase2", true);
		return EBTNodeResult::Succeeded;
	}

	else
	{
		Boss->_StatCom->SetHp(Boss->_StatCom->GetMaxHp());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("GimmickExecuted", false);
        return EBTNodeResult::Failed;
    }


}
