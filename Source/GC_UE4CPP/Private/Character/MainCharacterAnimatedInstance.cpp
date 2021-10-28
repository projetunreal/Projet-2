// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacterAnimatedInstance.h"
#include "Character/MyCharacter.h"


void UMainCharacterAnimatedInstance::NativeUpdateAnimation(const float DeltaTime)
{
	UMyAnimatedInstance::NativeUpdateAnimation(DeltaTime);
	if(MainActor)
	{
		bSit = MainActor->IsSit();
	}
	else 
	{	
		MainActor = Cast<AMyCharacter>(GetOwningActor());
	}
}