// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::OnClickPlayButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Game");
	UE_LOG(LogTemp, Warning, TEXT("Play button pressed"))
}

void UMainMenuWidget::OnClickQuitButton()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	UE_LOG(LogTemp, Warning, TEXT("Quit button pressed"))
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
