// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTargetPointSelection.h"
#include "EnnemyTargetPoint.h"
#include "EnnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());

    if (AICon)
    {

        UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
        AEnnemyTargetPoint* CurrentPoint = Cast<AEnnemyTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

        TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();

        int32 RandomIndex;

        AEnnemyTargetPoint* NextTargetPoint = nullptr;

        do
        {
            RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);

            NextTargetPoint = Cast<AEnnemyTargetPoint>(AvailableTargetPoints[RandomIndex]);
        } while (CurrentPoint == NextTargetPoint);

        BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
