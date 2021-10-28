// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"

#include "FoodSpot.generated.h"

class UStaticMeshComponent;
class AFood;
UCLASS()
class GC_UE4CPP_API AFoodSpot final : public AActor
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
	
	bool IsFoodOn() const;
	
	void SetFood(AFood* Food);
	
	FORCEINLINE AFood* GetFood() const {return FoodHeld;};
	FORCEINLINE UStaticMeshComponent* GetMesh() const {return StaticMesh;};
	FORCEINLINE AActor* GetFoodSpotUserPlace() const {return FoodSpotUserPlace;};
};
