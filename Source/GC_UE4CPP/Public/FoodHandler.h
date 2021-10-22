// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.h"
#include "FoodHandler.generated.h"

UCLASS()
class GC_UE4CPP_API AFoodHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodHandler();

	UPROPERTY(EditAnywhere)
		TArray<AFood*> Foods;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetFoodCount();
	void Remove(AFood* Food);
	void AddFood(AFood* Food);
};
