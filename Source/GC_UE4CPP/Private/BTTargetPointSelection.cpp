// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTargetPointSelection.h"
#include "EnnemyTargetPoint.h"
#include "EnnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		AAICharacter* AIChar = AICon->GetAICharacter();
		if (AIChar)
		{
			UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
			if (BlackboardComp)
			{
				if (GetWorld())
				{
					UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
					if (NavSystem)
					{
						FVector StartPos = AIChar->GetActorLocation();
						FNavLocation EndPos = FNavLocation(StartPos);
						
						if (NavSystem->GetRandomReachablePointInRadius(StartPos, AIChar->GetPatrolDistance(), EndPos))
						{
							BlackboardComp->SetValueAsVector("PatrolLocation1", EndPos.Location);
							if (NavSystem->GetRandomReachablePointInRadius(StartPos, AIChar->GetPatrolDistance(), EndPos))
							{
								BlackboardComp->SetValueAsVector("PatrolLocation2", EndPos.Location);
								BlackboardComp->SetValueAsBool("ReachedPatrolLocation1", false);
								BlackboardComp->SetValueAsBool("ReachedPatrolLocation2", false);
								BlackboardComp->SetValueAsBool("PatrolLocationsSet", true);

								return EBTNodeResult::Succeeded;
							}
						}
					}
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
