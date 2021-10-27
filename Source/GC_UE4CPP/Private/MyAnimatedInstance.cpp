// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimatedInstance.h"
#include "FoodUserActor.h"
#include "MyGC_UE4CPPGameModeBase.h"

UMyAnimatedInstance::UMyAnimatedInstance()
{
	bMove = false;
	bHold = false;
	bWin = false;
	bLoose = false;
	//
	//
}

void UMyAnimatedInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Actor && GameMode )
	{
		bMove = (Actor->GetVelocity().Size() > 0);
		bHold = Actor->IsHoldingFood();

		bLoose = GameMode->IsLoose();
		bWin = GameMode->IsWin();

	}
	else
	{
		Actor = Cast<AFoodUserActor>(GetOwningActor());
		GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	}
}
