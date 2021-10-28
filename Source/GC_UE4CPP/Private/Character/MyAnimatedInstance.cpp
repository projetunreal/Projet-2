// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MyAnimatedInstance.h"
#include "Character/FoodUserActor.h"
#include "UI/MyGC_UE4CPPGameModeBase.h"

UMyAnimatedInstance::UMyAnimatedInstance()
{
	bMove = false;
	bHold = false;
	bWin = false;
	bLose = false;
}

void UMyAnimatedInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (Actor && GameMode)
	{
		bMove = (Actor->GetVelocity().Size() > 0);
		bHold = Actor->IsHoldingFood();
		bLose = GameMode->IsLose();
		bWin = GameMode->IsWin();

	}
	else
	{
		Actor = Cast<AFoodUserActor>(GetOwningActor());
		GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	}
}