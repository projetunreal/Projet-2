// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDropFoodOnSpot.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FoodSpot.h"
#include "AICharacter.h"


EBTNodeResult::Type UBTDropFoodOnSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AICon) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	AAICharacter* AIChar = AICon->GetAICharacter();
	if (!AIChar) return EBTNodeResult::Failed;

	AFoodSpot* FoodSpot = Cast<AFoodSpot>(BlackboardComp->GetValueAsObject("FoodSpot"));
	if (!FoodSpot) return EBTNodeResult::Failed;

	if (!FoodSpot->IsFoodOn())
	{
		AIChar->PutFoodOnSpot(FoodSpot);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}