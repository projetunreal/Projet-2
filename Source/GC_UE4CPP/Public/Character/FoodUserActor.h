// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	virtual void Tick(const float DeltaTime) override;
	virtual void BeginPlay() override;
	
public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool IsHoldingFood() const;

	void DropFood();
	void PickUpFood(AFood* Food);
	
	void PutFoodOnSpot(AFoodSpot* Spot);
	void PickUpFoodFromSpot(AFoodSpot* Spot);
	
	FORCEINLINE AFood* GetFood() const { return FoodHeld; };
	
private:
	 float BaseSpeed;
};
