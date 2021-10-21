// Fill out your copyright notice in the Description page of Project Settings.


#include "BTFoodSpotSelection.h"
#include "EnnemyAIController.h"
#include "FoodSpot.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTFoodSpotSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());

    if (AICon)
    {
        UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
        AFoodSpot* FoodSpot = AICon->GetFoodSpotHandler()->GetRandomEmptyFoodSpot();
        if (FoodSpot)
        {
            BlackboardComp->SetValueAsObject("FoodSpot", FoodSpot);
            AActor* FoodSpotUserPlace = FoodSpot->GetFoodSpotUserPlace();
            if (FoodSpotUserPlace)
            {
                BlackboardComp->SetValueAsObject("FoodSpotUserPlace", FoodSpotUserPlace);
                return EBTNodeResult::Succeeded;
            }
        }
    }
    return EBTNodeResult::Failed;
}
