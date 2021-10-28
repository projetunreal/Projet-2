// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/FoodSpotHandler.h"
#include "Food/FoodSpot.h"

// Sets default values
AFoodSpotHandler::AFoodSpotHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodSpotHandler::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFoodSpotHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFoodSpot* AFoodSpotHandler::GetRandomEmptyFoodSpot()
{
	TArray<AFoodSpot*> EmptyFoodSpots;
	for (int i = 0; i < FoodSpots.Num(); i++)
	{
		AFoodSpot* FoodSpot = FoodSpots[i];
		if (FoodSpot)
		{
			if (!FoodSpot->GetFood())
			{
				EmptyFoodSpots.Add(FoodSpot);
			}
		}
	}

	if (EmptyFoodSpots.Num() == 0)
	{
		return nullptr;
	}
	else
	{
		return EmptyFoodSpots[FMath::RandRange(0, EmptyFoodSpots.Num() - 1)];
	}
}

