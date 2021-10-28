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

private:

	UPROPERTY(EditAnywhere)
		TArray<AFood*> Foods;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this actor's properties
	AFoodHandler();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE int GetFoodCount() const { return Foods.Num(); };

	void Remove(AFood* Food);
	void AddFood(AFood* Food);
};
