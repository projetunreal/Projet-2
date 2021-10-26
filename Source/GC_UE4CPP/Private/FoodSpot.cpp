// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSpot.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFoodSpot::AFoodSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
void AFoodSpot::SetFood(AFood* food)
{
	FoodHeld = food;

}
AFood* AFoodSpot::GetFood()
{
	return FoodHeld;

}

AActor* AFoodSpot::GetFoodSpotUserPlace()
{
	return FoodSpotUserPlace;
}
