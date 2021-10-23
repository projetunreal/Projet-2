// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FoodUserActor.h"
#include "AICharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AAICharacter : public AFoodUserActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		float PatrolDistance = 5000;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this character's properties
	AAICharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE float GetPatrolDistance() const { return PatrolDistance; }

	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; };
};
