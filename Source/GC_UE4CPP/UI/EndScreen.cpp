// Fill out your copyright notice in the Description page of Project Settings.


#include "EndScreen.h"

#include "MyGC_UE4CPPGameModeBase.h"


void UEndScreen::OnClickButton()
{
	const AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->ToggleMouseCursor(false);
	GameMode->TogglePlayerInput(true);
	
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
