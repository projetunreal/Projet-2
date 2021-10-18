// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodSpot.h"
#include "FoodSpotHandler.generated.h"

UCLASS()
class GC_UE4CPP_API AFoodSpotHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodSpotHandler();

	UPROPERTY(EditAnywhere)
		TArray<AFoodSpot*> FoodSpots;

private:
	int EmptyFoodSpotsCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AFoodSpot* GetRandomEmptyFoodSpot();
	void IncreaseEmptyFoodSpotsCount();
	void DecreaseEmptyFoodSpotsCount();
};
