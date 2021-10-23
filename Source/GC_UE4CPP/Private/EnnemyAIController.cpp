// Fill out your copyright notice in the Description page of Project Settings.

#include "EnnemyAIController.h"
#include "Food.h"
#include "MyGC_UE4CPPGameModeBase.h"
#include "AICharacter.h"
#include "EnnemyTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MyCharacter.h"
#include "FoodSpotHandler.h"


void AEnnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BlackboardComp->GetValueAsBool("bCanSeePlayer"))
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
			BlackboardComp->SetValueAsBool("bGameOver", true);
		}
	}

	AFood* Food = Cast<AFood>(BlackboardComp->GetValueAsObject("Food"));
	if (Food)
	{
		BlackboardComp->SetValueAsBool("bFoodOnFloor", Food->GetOnFloor());
	}
}

AEnnemyAIController::AEnnemyAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";

	SetGenericTeamId(FGenericTeamId(1));
}

void AEnnemyAIController::SetFoodSpotHandler(AFoodSpotHandler* SomeFoodSpotHandler)
{
	FoodSpotHandler = SomeFoodSpotHandler;
}

void AEnnemyAIController::JobIsDone()
{
	BlackboardComp->SetValueAsBool("bJobDone", true);
}

bool AEnnemyAIController::IsJobDone() const
{
	return BlackboardComp->GetValueAsBool("bJobDone");
}

void AEnnemyAIController::OnPossess(APawn* SomePawn)
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

void AEnnemyAIController::OnTargetUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AMyCharacter* const Char = Cast<AMyCharacter>(Actor);
	if (Char)
	{
		BlackboardComp->SetValueAsBool("bCanSeePlayer", Stimulus.WasSuccessfullySensed());
		TargetActor = Actor;
	}
}

void AEnnemyAIController::SetupPerceptionSystem()
{
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnnemyAIController::OnTargetUpdated);
}