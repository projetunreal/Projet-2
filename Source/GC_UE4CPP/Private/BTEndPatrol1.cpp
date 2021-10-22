// Fill out your copyright notice in the Description page of Project Settings.

#include "EnnemyAIController.h"
#include "BTEndPatrol1.h"

EBTNodeResult::Type UBTEndPatrol1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool("ReachedPatrolLocation1", true);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
