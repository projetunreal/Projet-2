// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuGameModeBase.h"

#include "UI/MainMenuWidget.h"
#include "Blueprint/UserWidget.h"

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
    
    const FInputModeUIOnly FInputMode;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->SetInputMode(FInputMode);
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
    		
	if(MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
