// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BehaviourTree/BTEndPatrol2.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTEndPatrol2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AICon) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	BlackboardComp->SetValueAsBool("bReachedPatrolLocation2", true);
	return EBTNodeResult::Succeeded;
}