// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/Food.h"

// Sets default values
AFood::AFood()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box Collider"));

	Box->SetupAttachment(StaticMesh);
	Box->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f), false);
}