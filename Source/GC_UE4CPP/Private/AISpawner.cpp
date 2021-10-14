// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "AISpawner.h"

// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AICount = 0;
}

void AAISpawner::IncreaseAICount()
{
	AIInsideRoomCount++;
}

void AAISpawner::DecreaseAICount()
{
	AIInsideRoomCount--;
}

void AAISpawner::SpawnIA()
{
	if (AICharacterBP)
	{
		FActorSpawnParameters p;
		p.Owner = this;
	
		AAICharacter* AIChar = GetWorld()->SpawnActor<AAICharacter>(AICharacterBP, GetActorLocation() + FVector(0,0,125.549332), GetActorRotation(), p);
		SpawnedAI.Add(AIChar);

		IncreaseAICount();
	}
}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	BeginTime = GetWorld()->GetTimeSeconds();
	AIInsideRoomCount = 0;
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AAICharacter* AIChar;

	//despawn at entry with job done
	for (int i = AIInsideRoomCount-1; i >= 0; i--)
	{
		AIChar = SpawnedAI[i];
		if (AIChar->IsJobDone() && FVector::Distance(GetActorLocation(), AIChar->GetActorLocation()) < DestroyRadius)
		{
			AIChar->Destroy();
			SpawnedAI.RemoveAtSwap(i);

			RespawnTimes.Add(GetWorld()->GetTimeSeconds() + FMath::RandRange(RespawnMinCooldown, RespawnMaxCooldown));
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

