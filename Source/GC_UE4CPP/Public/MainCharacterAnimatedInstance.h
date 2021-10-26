// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimatedInstance.h"

#include "MainCharacterAnimatedInstance.generated.h"

class AMyCharacter;
UCLASS()
class GC_UE4CPP_API UMainCharacterAnimatedInstance : public UMyAnimatedInstance
{
	GENERATED_BODY()
public :
	AMyCharacter* MainActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool bSit = false ;
protected :
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
