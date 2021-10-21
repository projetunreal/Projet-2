// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyAIController.h"
#include "BTDropFood.h"

EBTNodeResult::Type UBTDropFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnnemyAIController* AICon = Cast<AEnnemyAIController>(OwnerComp.GetAIOwner());
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		if (BlackboardComp)
		{
			AAICharacter* AIChar = AICon->GetAICharacter();
			if (AIChar)
			{
				AFood* Food = AIChar->GetFood();
				if (Food)
				{
					AIChar->DropFood();
					BlackboardComp->SetValueAsBool("DroppedFood", true);
				}
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
