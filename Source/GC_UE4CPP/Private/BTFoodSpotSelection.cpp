// Fill out your copyright notice in the Description page of Project Settings.

#include "BTFoodSpotSelection.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FoodSpotHandler.h"
#include "FoodSpot.h"


EBTNodeResult::Type UBTFoodSpotSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if (!AICon) return EBTNodeResult::Failed;

    UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
    if (!BlackboardComp) return EBTNodeResult::Failed;

    AFoodSpotHandler* FoodSpotHandler = AICon->GetFoodSpotHandler();
    if (!FoodSpotHandler) return EBTNodeResult::Failed;

    AFoodSpot* FoodSpot = FoodSpotHandler->GetRandomEmptyFoodSpot();
    if (!FoodSpot) return EBTNodeResult::Failed;

    BlackboardComp->SetValueAsObject("FoodSpot", FoodSpot);

    AActor* FoodSpotUserPlace = FoodSpot->GetFoodSpotUserPlace();
    if (!FoodSpotUserPlace) return EBTNodeResult::Failed;

    BlackboardComp->SetValueAsObject("FoodSpotUserPlace", FoodSpotUserPlace);
    return EBTNodeResult::Succeeded;
}