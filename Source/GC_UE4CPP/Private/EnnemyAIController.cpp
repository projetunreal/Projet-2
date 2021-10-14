// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyAIController.h"



void AEnnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Blackboard->GetValueAsBool("CanSeePlayer"))
	{
		BlackboardComp->SetValueAsVector("LastKnownPlayerLocation", TargetActor->GetActorLocation());
		BlackboardComp->SetValueAsVector("LastKnownPlayerDirection", TargetActor->GetActorForwardVector());
	}
	else
	{
		FVector TargetLocation = AIChar->GetActorLocation() + BlackboardComp->GetValueAsVector("LastKnownPlayerDirection") *(AIChar->GetVelocity().Size() * DeltaTime + SearchDistance);
		BlackboardComp->SetValueAsVector("SearchPlayerLocation", TargetLocation);
	}
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
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnnemyTargetPoint::StaticClass(), EnnemyTargetPoints);

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