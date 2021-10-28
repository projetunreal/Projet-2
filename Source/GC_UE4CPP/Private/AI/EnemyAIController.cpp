// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"
#include "Food/Food.h"
#include "UI/MyGC_UE4CPPGameModeBase.h"
#include "AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Character/MyCharacter.h"
#include "Food/FoodSpotHandler.h"


void AEnemyAIController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BlackboardComp->GetValueAsBool("bCanSeePlayer"))
	{
		BlackboardComp->SetValueAsVector("LastKnownPlayerLocation", TargetActor->GetActorLocation());
		BlackboardComp->SetValueAsVector("LastKnownPlayerDirection", TargetActor->GetActorForwardVector());
	}
	else
	{
		const FVector TargetLocation = AIChar->GetActorLocation() + BlackboardComp->GetValueAsVector("LastKnownPlayerDirection") * (AIChar->GetVelocity().Size() * DeltaTime + SearchDistance);
		BlackboardComp->SetValueAsVector("SearchPlayerLocation", TargetLocation);
	}

	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		if (GameMode->IsWin() || GameMode->IsLose())
		{
			BlackboardComp->SetValueAsBool("bGameOver", true);
		}
	}

	AFood* Food = Cast<AFood>(BlackboardComp->GetValueAsObject("Food"));
	if (Food)
	{
		BlackboardComp->SetValueAsBool("bFoodOnFloor", Food->GetOnFloor());
	}
}

AEnemyAIController::AEnemyAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AEnemyAIController::JobIsDone() const
{
	BlackboardComp->SetValueAsBool("bJobDone", true);
}

bool AEnemyAIController::IsJobDone() const
{
	return BlackboardComp->GetValueAsBool("bJobDone");
}

void AEnemyAIController::OnPossess(APawn* SomePawn)
{
	Super::OnPossess(SomePawn);

	AIChar = Cast<AAICharacter>(SomePawn);
	if (!AIChar) return;

	UBehaviorTree* BehaviorTree = AIChar->GetBehaviorTree();
	if (BehaviorTree->BlackboardAsset)
	{
		if (BlackboardComp)
		{
			BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
			BlackboardComp->SetValueAsBool("bGameOver", false);

			if (FoodSpotHandler) BlackboardComp->SetValueAsObject("FoodSpotHandler", FoodSpotHandler);
		}
	}

	BehaviorComp->StartTree(*BehaviorTree);

	SetupPerceptionSystem();
}

void AEnemyAIController::OnTargetUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AMyCharacter* const Char = Cast<AMyCharacter>(Actor);
	if (Char)
	{
		BlackboardComp->SetValueAsBool("bCanSeePlayer", Stimulus.WasSuccessfullySensed());
		TargetActor = Actor;
	}
}

void AEnemyAIController::SetupPerceptionSystem()
{
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetUpdated);
}