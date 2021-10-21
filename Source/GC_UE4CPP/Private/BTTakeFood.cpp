// Fill out your copyright notice in the Description page of Project Settings.

#include "EnnemyAIController.h"
#include "BTTakeFood.h"

EBTNodeResult::Type UBTTakeFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
				AFood* Food = Cast<AFood>(BlackboardComp->GetValueAsObject("Food"));
				if (Food)
				{
					AIChar->PickUpFood(Food);
					BlackboardComp->SetValueAsBool("DroppedFood", false);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
