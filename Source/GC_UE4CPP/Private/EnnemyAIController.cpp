// Fill out your copyright notice in the Description page of Project Settings.

#include "EnnemyAIController.h"
#include "Food.h"
#include "MyGC_UE4CPPGameModeBase.h"




void AEnnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BlackboardComp->GetValueAsBool("CanSeePlayer"))
	{
		BlackboardComp->SetValueAsVector("LastKnownPlayerLocation", TargetActor->GetActorLocation());
		BlackboardComp->SetValueAsVector("LastKnownPlayerDirection", TargetActor->GetActorForwardVector());
	}
	else
	{
		FVector TargetLocation = AIChar->GetActorLocation() + BlackboardComp->GetValueAsVector("LastKnownPlayerDirection") *(AIChar->GetVelocity().Size() * DeltaTime + SearchDistance);
		BlackboardComp->SetValueAsVector("SearchPlayerLocation", TargetLocation);
	}

	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		if (GameMode->IsWin() || GameMode->IsLoose())
		{
			BlackboardComp->SetValueAsBool("GameOver", true);
		}
	}

	AFood* Food = Cast<AFood>(BlackboardComp->GetValueAsObject("Food"));
	if (Food)
	{
		BlackboardComp->SetValueAsBool("FoodOnFloor", Food->GetOnFloor());
	}

	/*AFood* Food = Cast<AFood>(BlackboardComp->GetValueAsObject("Food"));
	if (Food && AIChar->IsHoldingFood())
	{
		BlackboardComp->SetValueAsVector("LastKnownFoodLocation", Food->GetActorLocation());
	}*/
}

AEnnemyAIController::AEnnemyAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";

	SetGenericTeamId(FGenericTeamId(1));
}

AAICharacter* AEnnemyAIController::GetAICharacter()
{
	return AIChar;
}

void AEnnemyAIController::SetFoodSpotHandler(AFoodSpotHandler* SomeFoodSpotHandler)
{
	FoodSpotHandler = SomeFoodSpotHandler;
}

AFoodSpotHandler* AEnnemyAIController::GetFoodSpotHandler()
{
	return FoodSpotHandler;
}

void AEnnemyAIController::JobIsDone()
{
	BlackboardComp->SetValueAsBool("JobIsDone", true);
}

bool AEnnemyAIController::IsJobDone()
{
	return BlackboardComp->GetValueAsBool("JobIsDone");
}

void AEnnemyAIController::OnPossess(APawn* SomePawn)
{
	Super::OnPossess(SomePawn);

	AIChar = Cast<AAICharacter>(SomePawn);
	if (AIChar)
	{
		if (AIChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
			BlackboardComp->SetValueAsObject("FoodSpotHandler", FoodSpotHandler);
			BlackboardComp->SetValueAsBool("GameOver", false);
		}

		BehaviorComp->StartTree(*AIChar->BehaviorTree);

		SetupPerceptionSystem();
	}
}

void AEnnemyAIController::OnTargetUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (auto const Ch = Cast<AMyCharacter>(Actor))
	{
		BlackboardComp->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
		TargetActor = Actor;
	}
}

void AEnnemyAIController::SetupPerceptionSystem()
{
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnnemyAIController::OnTargetUpdated);
}