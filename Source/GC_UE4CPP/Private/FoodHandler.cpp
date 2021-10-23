// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodHandler.h"
#include "Food.h"


// Sets default values
AFoodHandler::AFoodHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFoodHandler::AddFood(AFood* Food)
{
	Foods.Add(Food);
}

// Called every frame
void AFoodHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFoodHandler::Remove(AFood* Food)
{
	Foods.RemoveSwap(Food);
}

