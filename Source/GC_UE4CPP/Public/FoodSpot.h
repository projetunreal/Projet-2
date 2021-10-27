// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"

#include "FoodSpot.generated.h"

class UStaticMeshComponent;
class AFood;
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
	
	void SetFood(AFood* Food);
	AFood* GetFood();

public:	
	UStaticMeshComponent* getMesh();
	AActor* GetFoodSpotUserPlace();
};
