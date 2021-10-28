// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::OnClickPlayButton()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) {return;}

	PlayerController->bShowMouseCursor = false;
	PlayerController->bEnableClickEvents = false;
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
}

void UMainMenuWidget::OnClickQuitButton()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) {return;}

	PlayerController->bShowMouseCursor = false;
	PlayerController->bEnableClickEvents = false;
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickPlayButton);
	}
	if(QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickQuitButton);
	}
}
