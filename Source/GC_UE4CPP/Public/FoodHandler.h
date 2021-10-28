// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FoodHandler.generated.h"

class AFood;

UCLASS()
class GC_UE4CPP_API AFoodHandler final : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<AFood*> Foods;

public:

	FORCEINLINE int GetFoodCount() const {return Foods.Num();};

	void Remove(AFood* Food);
	void AddFood(AFood* Food);
};
