// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Food.h"

#include "FoodUserActor.generated.h"

UCLASS()
class  GC_UE4CPP_API AFoodUserActor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFoodUserActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		AFood* FoodHeld;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsHoldingFood();
	void DropFood();
protected :
	void PickUpFood(AFood* food);
	
	virtual void FoodAction();
	void PutFoodOnSpot(USceneComponent* obj);
	
};
