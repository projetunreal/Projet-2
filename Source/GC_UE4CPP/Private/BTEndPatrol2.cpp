// Fill out your copyright notice in the Description page of Project Settings.

#include "EnnemyAIController.h"
#include "BTEndPatrol2.h"

EBTNodeResult::Type UBTEndPatrol2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool("ReachedPatrolLocation2", true);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}