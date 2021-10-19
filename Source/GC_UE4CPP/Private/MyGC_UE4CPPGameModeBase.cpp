// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGC_UE4CPPGameModeBase.h"

AMyGC_UE4CPPGameModeBase::AMyGC_UE4CPPGameModeBase()
{
	
}

void AMyGC_UE4CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyGC_UE4CPPGameModeBase::WinGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Game Won"));

	//Disable player input
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetPawn()->DisableInput(PlayerController);

	//Change animation
	bPlayerWon = true;

	//Get mouse cursor
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;

	//Widget spawn
	if (EndScreenClass)
	{
		EndScreenWidget = CreateWidget<UEndScreen>(GetWorld(), EndScreenClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport();

			UTextBlock* Text = EndScreenWidget->WinLoseTextBlock;
			Text->SetText(FText::FromString("You won!"));
			Text->SetColorAndOpacity(FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f)));
			Text->Font.Size = 138;
			
		}
	}
	
}

void AMyGC_UE4CPPGameModeBase::LoseGame()
{
	//Disable player input
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetPawn()->DisableInput(PlayerController);

	//Change animation
	bPlayerLost = true;

	//Get mouse cursor
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;

	//Widget spawn
	if (EndScreenClass)
	{
		EndScreenWidget = CreateWidget<UEndScreen>(GetWorld(), EndScreenClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport();

			UTextBlock* Text = EndScreenWidget->WinLoseTextBlock;
			Text->SetText(FText::FromString("You lost!"));
			Text->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f)));
			Text->Font.Size = 138;
			
		}
	}
}

