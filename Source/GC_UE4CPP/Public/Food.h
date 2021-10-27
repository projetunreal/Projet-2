// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Food.generated.h"
class AFoodHandler;
UCLASS()
class GC_UE4CPP_API AFood : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AFood();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Box;
	UStaticMeshComponent* GetMesh();
	UBoxComponent* GetBox();

private:

	bool bOnFloor = false;
	AFoodHandler* FoodHandler;

public:

	FORCEINLINE bool GetOnFloor() const { return bOnFloor; };
	FORCEINLINE void SetOnFloor(bool bFoodAccessible) { bOnFloor = bFoodAccessible; };

	FORCEINLINE AFoodHandler* GetFoodHandler() { return FoodHandler; };
	FORCEINLINE void SetFoodHandler(AFoodHandler* SomeFoodHandler) { FoodHandler = SomeFoodHandler; };
};