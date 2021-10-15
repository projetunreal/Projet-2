// Fill out your copyright notice in the Description page of Project Settings.
#include "EndJob.h"
#include "EnnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UEndJob::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());

    if (AICon)
    {
        AICon->GetBlackboardComp()->SetValueAsBool("JobIsDone", true);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
