// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box Collider"));
}

UStaticMeshComponent* AFood::GetMesh()
{
	return StaticMesh;
}

UBoxComponent* AFood::GetBox()
{
	return Box;
}

void AFood::SetOnFloor(bool FoodAccessible)
{
	bOnFloor = FoodAccessible;
}

bool AFood::GetOnFloor()
{
	return bOnFloor;
}

