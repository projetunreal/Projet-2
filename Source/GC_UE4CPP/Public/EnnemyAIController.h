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

	virtual void OnPossess(APawn* SomePawn) override;

public:

	AEnnemyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return EnnemyTargetPoints; }
};
