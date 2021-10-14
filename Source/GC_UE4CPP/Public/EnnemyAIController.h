// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICharacter.h"
#include "EnnemyTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MyCharacter.h"

#include "EnnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AEnnemyAIController : public AAIController
{
	GENERATED_BODY()

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;

	TArray<AActor*> EnnemyTargetPoints;
	
	AActor* TargetActor;

	AAICharacter* AIChar;

	float SearchDistance = 15;

	//float LastTimePlayerWasSeen = 0;
	
	virtual void OnPossess(APawn* SomePawn) override;

	UFUNCTION()
	void OnTargetUpdated(AActor* Actor, FAIStimulus const Stimulus);

	void SetupPerceptionSystem();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AEnnemyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return EnnemyTargetPoints; }

	AAICharacter* GetAICharacter();

	void JobIsDone();
	bool IsJobDone();
};
