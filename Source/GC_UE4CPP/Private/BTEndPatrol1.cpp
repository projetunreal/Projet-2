// Fill out your copyright notice in the Description page of Project Settings.

#include "BTEndPatrol1.h"
#include "EnnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTEndPatrol1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());
	if (!AICon) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	BlackboardComp->SetValueAsBool("bReachedPatrolLocation1", true);
	return EBTNodeResult::Succeeded;
}
