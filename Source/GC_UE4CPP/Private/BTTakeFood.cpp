// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTakeFood.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Food.h"
#include "AICharacter.h"


EBTNodeResult::Type UBTTakeFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AICon) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	AAICharacter* AIChar = AICon->GetAICharacter();
	if (!AIChar) return EBTNodeResult::Failed;

	AFood* Food = Cast<AFood>(BlackboardComp->GetValueAsObject("Food"));
	if (!Food) return EBTNodeResult::Failed;

	AIChar->PickUpFood(Food);
	BlackboardComp->SetValueAsBool("bDroppedFood", false);
	return EBTNodeResult::Succeeded;
}
