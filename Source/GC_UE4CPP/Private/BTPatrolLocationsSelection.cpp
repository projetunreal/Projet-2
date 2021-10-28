// Fill out your copyright notice in the Description page of Project Settings.


#include "BTPatrolLocationsSelection.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AICharacter.h"

EBTNodeResult::Type UBTPatrolLocationsSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AICon) return EBTNodeResult::Failed;

	AAICharacter* AIChar = AICon->GetAICharacter();
	if (!AIChar) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem) return EBTNodeResult::Failed;

	const FVector StartPos = AIChar->GetActorLocation();
	FNavLocation EndPos = FNavLocation(StartPos);

	if (NavSystem->GetRandomReachablePointInRadius(StartPos, AIChar->GetPatrolDistance(), EndPos))
	{
		BlackboardComp->SetValueAsVector("PatrolLocation1", EndPos.Location);
		if (NavSystem->GetRandomReachablePointInRadius(StartPos, AIChar->GetPatrolDistance(), EndPos))
		{
			BlackboardComp->SetValueAsVector("PatrolLocation2", EndPos.Location);
			BlackboardComp->SetValueAsBool("bReachedPatrolLocation1", false);
			BlackboardComp->SetValueAsBool("bReachedPatrolLocation2", false);
			BlackboardComp->SetValueAsBool("bPatrolLocationsSet", true);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}