// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Food.generated.h"

class AFoodHandler;
class AFoodUserActor;
UCLASS()
class GC_UE4CPP_API AFood final : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AFood();
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Box;
	
	FORCEINLINE UStaticMeshComponent* GetMesh() const {return StaticMesh;};
	FORCEINLINE UBoxComponent* GetBox() const {return Box;};

	FORCEINLINE bool GetOnFloor() const {return bOnFloor;};
	FORCEINLINE void SetOnFloor(const bool bFoodAccessible) {bOnFloor = bFoodAccessible;};

	FORCEINLINE AFoodHandler* GetFoodHandler() const {return FoodHandler;};
	FORCEINLINE void SetFoodHandler(AFoodHandler* SomeFoodHandler) {FoodHandler = SomeFoodHandler;};
	
	FORCEINLINE AFoodUserActor* GetFoodUserActor() const { return FoodUser; };
	FORCEINLINE void SetFoodUserActor(AFoodUserActor* FoodUserActor) {this->FoodUser = FoodUserActor;};

private:
	bool bOnFloor = false;
	AFoodHandler* FoodHandler;
	AFoodUserActor* FoodUser;
};