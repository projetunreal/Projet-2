// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/FoodSpot.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFoodSpot::AFoodSpot()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
}

bool AFoodSpot::IsFoodOn() const
{
	return FoodHeld != nullptr;
}

void AFoodSpot::SetFood(AFood* Food)
{
	FoodHeld = Food;
}