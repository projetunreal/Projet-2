// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Food.h"

#include "FoodSpot.generated.h"

UCLASS()
class GC_UE4CPP_API AFoodSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodSpot();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
		AFood* FoodHeld;

	UPROPERTY(EditAnywhere)
		AActor* FoodSpotUserPlace;
	
	bool IsFoodOn();
	
	void SetFood(AFood* food);
	AFood* GetFood();

public:	
	UStaticMeshComponent* getMesh();
	AActor* GetFoodSpotUserPlace();
};
