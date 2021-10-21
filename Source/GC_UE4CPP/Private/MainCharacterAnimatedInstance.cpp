// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimatedInstance.h"




void UMainCharacterAnimatedInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	UMyAnimatedInstance::NativeUpdateAnimation(DeltaSeconds);
	if(MainActor)
	{
		bSit = MainActor->IsSit();
	}
	else 
	{	
		MainActor = Cast<AMyCharacter>(GetOwningActor());
	}
}
