// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviourTree/BTDropFood.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AICharacter.h"


EBTNodeResult::Type UBTDropFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AICon) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	AAICharacter* AIChar = AICon->GetAICharacter();
	if (!AIChar) return EBTNodeResult::Failed;

	AFood* Food = AIChar->GetFood();
	if (Food)
	{
		AIChar->DropFood();
		BlackboardComp->SetValueAsBool("bDroppedFood", true);
	}
	return EBTNodeResult::Succeeded;
}