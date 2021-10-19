// Fill out your copyright notice in the Description page of Project Settings.


#include "EndScreen.h"

UEndScreen::UEndScreen(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UEndScreen::OnClickButton()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UEndScreen::NativeConstruct()
{
	Super::NativeConstruct();
	if(PlayAgainButton)
	{
		PlayAgainButton->OnClicked.AddDynamic(this, &UEndScreen::OnClickButton);
	}
}
