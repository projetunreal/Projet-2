// Fill out your copyright notice in the Description page of Project Settings.
#include "AISpawner.h"
#include "Math/UnrealMathUtility.h"
#include "FoodUserActor.h"
#include "EnnemyAIController.h"


// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AICount = 0;
}

void AAISpawner::SpawnIA()
{
	if (AICharacterBP)
	{
		FActorSpawnParameters p;
		p.Owner = this;
		
		FVector AICharPos = GetActorLocation() + FVector(0, 0, 125.549332);
		AAICharacter* AIChar = GetWorld()->SpawnActor<AAICharacter>(AICharacterBP, AICharPos, GetActorRotation(), p);
		AEnnemyAIController* AICon = Cast<AEnnemyAIController>(AIChar->GetController());
		if (AICon)
		{
			UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
			BlackboardComp->SetValueAsObject("Spawner", this);
			AICon->SetFoodSpotHandler(FoodSpotHandler);

			TSubclassOf<AFood> FoodBP = AIChar->GetFoodBP();
			if (FoodBP)
			{
				p.Owner = AIChar;
				AFood* Food = GetWorld()->SpawnActor<AFood>(FoodBP, AICharPos, GetActorRotation(), p);
				AIChar->PickUpFood(Food);
				BlackboardComp->SetValueAsObject("Food", Food);
			}
			SpawnedAI.Add(AIChar);
		}
	}
}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	BeginTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AAICharacter* AIChar;

	//despawn at entry with job done
	int AIInsideRoomCount = SpawnedAI.Num();
	for (int i = AIInsideRoomCount-1; i >= 0; i--)
	{
		AIChar = SpawnedAI[i];
		AEnnemyAIController* AIController = Cast<AEnnemyAIController>(AIChar->GetController());
		if (AIController)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%i"), AIInsideRoomCount);
			if (AIController->IsJobDone() && FVector::Distance(GetActorLocation(), AIChar->GetActorLocation()) < DestroyRadius)
			{
				AIChar->Destroy();
				SpawnedAI.RemoveAtSwap(i);

				RespawnTimes.Add(GetWorld()->GetTimeSeconds() + FMath::RandRange(RespawnMinCooldown, RespawnMaxCooldown));
			}
		}
	}

	//spawn
	if (AICount == 0)
	{
		SpawnIA();
		SpawnIA();
		AICount+= 2;
		//UE_LOG(LogTemp, Warning, TEXT("pop"));
	}
	else if(AICount == 2 && GetWorld()->GetTimeSeconds() - BeginTime > 60)
	{
		SpawnIA();
		AICount++;
	}

	//respawn
	for (int i = 0; i < RespawnTimes.Num(); i++)
	{
		if (RespawnTimes[i] - GetWorld()->GetTimeSeconds() < 0 || AIInsideRoomCount == 0)
		{
			SpawnIA();
			RespawnTimes.RemoveAtSwap(i);
		}
	}
}

