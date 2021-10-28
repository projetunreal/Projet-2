// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"

#include "EnemyAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class AAICharacter;
class AFoodSpotHandler;


UCLASS()
class GC_UE4CPP_API AEnemyAIController final : public AAIController
{
	GENERATED_BODY()

private:
	AFoodSpotHandler* FoodSpotHandler;
	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;

	AActor* TargetActor;
	AAICharacter* AIChar;

	UPROPERTY(EditAnywhere)
		float SearchDistance = 15;

	virtual void OnPossess(APawn* SomePawn) override;

	void SetupPerceptionSystem();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AEnemyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const {return BlackboardComp;}
	FORCEINLINE AAICharacter* GetAICharacter() const {return AIChar;};
	FORCEINLINE AFoodSpotHandler* GetFoodSpotHandler() const {return FoodSpotHandler;};

	FORCEINLINE void SetFoodSpotHandler(AFoodSpotHandler* SomeFoodSpotHandler) { FoodSpotHandler = SomeFoodSpotHandler; };

	UFUNCTION()
		void OnTargetUpdated(AActor* Actor, FAIStimulus const Stimulus);

	void JobIsDone() const;
	bool IsJobDone() const;
};