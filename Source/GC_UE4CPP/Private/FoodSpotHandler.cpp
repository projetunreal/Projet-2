// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSpotHandler.h"

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
	EmptyFoodSpotsCount = FoodSpots.Num();
}

// Called every frame
void AFoodSpotHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFoodSpot* AFoodSpotHandler::GetRandomEmptyFoodSpot()
{
	if (EmptyFoodSpotsCount == 0)
	{
		return nullptr;
	}
	else
	{
		return Cast<AFoodSpot>(FoodSpots[FMath::RandRange(0, FoodSpots.Num() - 1)]);
	}
	
}

void AFoodSpotHandler::IncreaseEmptyFoodSpotsCount()
{
	EmptyFoodSpotsCount++;
}

void AFoodSpotHandler::DecreaseEmptyFoodSpotsCount()
{
	EmptyFoodSpotsCount--;
}

