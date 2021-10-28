// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AISpawner.h"
#include "Math/UnrealMathUtility.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/FoodUserActor.h"
#include "Food/FoodSpotHandler.h"
#include "Food/FoodHandler.h"
#include "Food/FoodSpot.h"
#include "Food/Food.h"
#include "AI/AICharacter.h"


// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AICount = 0;
}

void AAISpawner::SpawnIa()
{
	//AI Character creation
	if (!AICharacterBP) return;
	FActorSpawnParameters p;
	p.Owner = this;
	const FVector AICharPos = GetActorLocation() + FVector(0, 0, 1) * Cast<AAICharacter>(AICharacterBP->GetDefaultObject())->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	AAICharacter* AIChar = GetWorld()->SpawnActor<AAICharacter>(AICharacterBP, AICharPos, GetActorRotation(), p);
	if (!AIChar) return;

	SpawnedAI.Add(AIChar);
	AEnemyAIController* AICon = Cast<AEnemyAIController>(AIChar->GetController());
	if (!AICon) return;

	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	if (!BlackboardComp) return;

	BlackboardComp->SetValueAsObject("Spawner", this);

	if (!FoodSpotHandler) return;
	AICon->SetFoodSpotHandler(FoodSpotHandler);

	if (!FoodHandler || !(FoodHandler->GetFoodCount() < 5) || !FoodBP) return;

	//Food creation
	AFood* Food = GetWorld()->SpawnActor<AFood>(FoodBP, AICharPos, GetActorRotation(), p);

	//Initialization
	Food->SetOnFloor(false);
	FoodHandler->AddFood(Food);
	Food->SetFoodHandler(FoodHandler);

	//Attaching to food user
	AIChar->PickUpFood(Food);
	BlackboardComp->SetValueAsObject("Food", Food);
}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();

	BeginTime = GetWorld()->GetTimeSeconds();

	AFoodSpot* FoodSpot = FoodSpotHandler->GetRandomEmptyFoodSpot();
	if (!FoodSpot) return;

	//Food creation
	FActorSpawnParameters p;
	p.Owner = this;
	AFood* Food = GetWorld()->SpawnActor<AFood>(FoodBP, FoodSpot->GetActorLocation(), GetActorRotation(), p);

	//Initialization
	Food->SetOnFloor(false);
	FoodHandler->AddFood(Food);
	Food->SetFoodHandler(FoodHandler);

	//Attaching to food spot
	Food->GetMesh()->SetSimulatePhysics(false);
	Food->GetMesh()->SetCollisionProfileName(TEXT("IgnoreAll"));
	Food->GetBox()->SetCollisionProfileName(TEXT("IgnoreAll"));
	Food->StaticMesh->AttachToComponent(FoodSpot->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));

	FoodSpot->SetFood(Food);
}

// Called every frame
void AAISpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Destroy at entry with job done
	const int AIInsideRoomCount = SpawnedAI.Num();
	for (int i = AIInsideRoomCount-1; i >= 0; i--)
	{
		AAICharacter* AIChar = SpawnedAI[i];
		if (!AIChar) return;

		AEnemyAIController* AIController = Cast<AEnemyAIController>(AIChar->GetController());
		if (!AIController) return;

		if (AIController->IsJobDone() && FVector::Distance(GetActorLocation(), AIChar->GetActorLocation()) < DestroyRadius)
		{
			AIChar->DestroySightCone();
			AIChar->Destroy();
			SpawnedAI.RemoveAtSwap(i);

			RespawnTimes.Add(GetWorld()->GetTimeSeconds() + FMath::RandRange(RespawnMinCooldown, RespawnMaxCooldown));
		}
	}

	//spawn
	if (AICount == 0)
	{
		SpawnIa();
		SpawnIa();
		AICount+= 2;
	}
	else if(AICount == 2 && GetWorld()->GetTimeSeconds() - BeginTime > 60)
	{
		SpawnIa();
		AICount++;
	}

	//respawn
	for (int i = 0; i < RespawnTimes.Num(); i++)
	{
		if (RespawnTimes[i] - GetWorld()->GetTimeSeconds() < 0 || AIInsideRoomCount == 0)
		{
			SpawnIa();
			RespawnTimes.RemoveAtSwap(i);
		}
	}
}

