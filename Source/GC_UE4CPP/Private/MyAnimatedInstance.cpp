// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimatedInstance.h"
UMyAnimatedInstance::UMyAnimatedInstance() 
{
	Moving = false;
	Holding = false;
}
void UMyAnimatedInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Actor)
	{
		Moving  = (Actor->GetVelocity().Size()>0);
		Holding = Actor->IsHoldingFood();
	}
	else
		Actor =Cast<AFoodUserActor>(GetOwningActor());
}
