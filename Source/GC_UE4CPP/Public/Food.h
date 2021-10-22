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

	void SetOnFloor(bool FoodAccessible);
	bool GetOnFloor();
	AFoodHandler* GetFoodHandler();
	void SetFoodHandler(AFoodHandler* SomeFoodHandler);
};