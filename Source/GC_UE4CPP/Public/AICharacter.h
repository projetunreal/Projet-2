// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FoodUserActor.h"
#include "AICharacter.generated.h"

class ASightCone;

UCLASS()
class GC_UE4CPP_API AAICharacter final : public AFoodUserActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "AI")
		float PatrolDistance = 5000;
	UPROPERTY(EditAnywhere, Category = "AI")
		float EyeHeightFromCenter = 40.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "AI")
		class ASightCone* SightCone;

	UPROPERTY(EditAnywhere, Category = "AI")
		class TSubclassOf<ASightCone> SightConeBP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FORCEINLINE float GetPatrolDistance() const {return PatrolDistance;}
	FORCEINLINE float GetEyeHeightFromCenter() const {return EyeHeightFromCenter;}

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const {return BehaviorTree;};
	
	void DestroySightCone() const;
};
