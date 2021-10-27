// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSpot.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFoodSpot::AFoodSpot()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
}

UStaticMeshComponent* AFoodSpot::getMesh()
{
	return StaticMesh;
}
bool AFoodSpot::IsFoodOn()
{
	return FoodHeld != nullptr;
}
void AFoodSpot::SetFood(AFood* Food)
{
	FoodHeld = Food;
}
AFood* AFoodSpot::GetFood()
{
	return FoodHeld;
}

AActor* AFoodSpot::GetFoodSpotUserPlace()
{
	return FoodSpotUserPlace;
}
