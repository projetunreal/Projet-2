// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyAIController.h"



AEnnemyAIController::AEnnemyAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";
}

void AEnnemyAIController::OnPossess(APawn* SomePawn)
{
	Super::OnPossess(SomePawn);

	AAICharacter* AIChar = Cast<AAICharacter>(SomePawn);

	if (AIChar)
	{
		if (AIChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnnemyTargetPoint::StaticClass(), EnnemyTargetPoints);

		BehaviorComp->StartTree(*AIChar->BehaviorTree);
	}
}

