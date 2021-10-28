// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FoodUserActor.generated.h"
class AFood;
class AFoodSpot;
UCLASS()
class  GC_UE4CPP_API AFoodUserActor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFoodUserActor();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere)
		AFood* FoodHeld;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds);
	virtual void BeginPlay();
	bool IsHoldingFood();

	void DropFood();
	void PickUpFood(AFood* Food);
	
	void PutFoodOnSpot(AFoodSpot* Spot);
	void PickUpFoodFromSpot(AFoodSpot* Spot);
	
	FORCEINLINE AFood* GetFood() { return FoodHeld; };
private:
	 float BaseSpeed;
};
