// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FoodUserActor.h"
#include "MyAnimatedInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class GC_UE4CPP_API UMyAnimatedInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMyAnimatedInstance();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool Moving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool Holding;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		AFoodUserActor* Actor;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
