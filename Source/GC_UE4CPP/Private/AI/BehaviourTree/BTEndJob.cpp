// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BehaviourTree/BTEndJob.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTEndJob::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if (!AICon) return EBTNodeResult::Failed;

    UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
    if (!BlackboardComp) return EBTNodeResult::Failed;

    BlackboardComp->SetValueAsBool("bJobDone", true);
    return EBTNodeResult::Succeeded;
}