// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "MyAnimatedInstance.generated.h"

class AFoodUserActor;
class AMyGC_UE4CPPGameModeBase;
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class GC_UE4CPP_API UMyAnimatedInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMyAnimatedInstance();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool bMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool bHold;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool bWin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool bLose;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		AFoodUserActor* Actor;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	AMyGC_UE4CPPGameModeBase* GameMode;
};