// Fill out your copyright notice in the Description page of Project Settings.

#include "EnnemyAIController.h"
#include "FoodSpot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTDropFoodOnSpot.h"

EBTNodeResult::Type UBTDropFoodOnSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		AFoodSpot* FoodSpot = Cast<AFoodSpot>(BlackboardComp->GetValueAsObject("FoodSpot"));
		if (!FoodSpot->IsFoodOn())
		{
			AICon->GetAICharacter()->PutFoodOnSpot(FoodSpot);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	return EBTNodeResult::Failed;
}
