// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGC_UE4CPPGameModeBase.h"

AMyGC_UE4CPPGameModeBase::AMyGC_UE4CPPGameModeBase()
{
	
}

void AMyGC_UE4CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	bGamePaused = false;
	
}

void AMyGC_UE4CPPGameModeBase::WinGame()
{
	if (bPlayerLost || bPlayerWon) {return;}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Game Won"));

	//Disable player input
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetPawn()->DisableInput(PlayerController);

	//Change animation
	bPlayerWon = true;

	ToggleMouseCursor(true);

	//Widget spawn
	if (EndScreenClass)
	{
		EndScreenWidget = CreateWidget<UEndScreen>(GetWorld(), EndScreenClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport();

			UTextBlock* Text = EndScreenWidget->WinLoseTextBlock;
			Text->SetText(FText::FromString("You won!"));
			Text->SetJustification(ETextJustify::Center);
			Text->SetColorAndOpacity(FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f)));			
		}
	}
	
}

void AMyGC_UE4CPPGameModeBase::LoseGame()
{
	if (bPlayerLost || bPlayerWon) {return;}
	
	//Disable player input
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetPawn()->DisableInput(PlayerController);

	//Change animation
	bPlayerLost = true;

	ToggleMouseCursor(true);
	
	//Widget spawn
	if (EndScreenClass)
	{
		EndScreenWidget = CreateWidget<UEndScreen>(GetWorld(), EndScreenClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport();

			UTextBlock* Text = EndScreenWidget->WinLoseTextBlock;
			Text->SetText(FText::FromString("You lost!"));
			Text->SetJustification(ETextJustify::Center);
			Text->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f)));
		}
	}
}

void AMyGC_UE4CPPGameModeBase::PauseGame()
{
	if (bGamePaused) {return;}
	
	//Widget spawn
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
		if (PauseWidget)
		{
			//Pause locally
			bGamePaused = true;
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			PlayerController->SetPause(bGamePaused);

			ToggleMouseCursor(true);


			//Add Pause Screen
			PauseWidget->AddToViewport();
			
			UTextBlock* Text = PauseWidget->PauseTextBlock;
			Text->SetText(FText::FromString("PAUSE"));
			Text->SetJustification(ETextJustify::Center);

			UImage* BackgroundImage = PauseWidget->BackgroundImage;
			BackgroundImage->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.5f, 0.1f));
		}
	}
}

void AMyGC_UE4CPPGameModeBase::UnpauseGame()
{
	bGamePaused = false;
	PauseWidget->RemoveFromViewport();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetPause(bGamePaused);

	ToggleMouseCursor(false);
}

void AMyGC_UE4CPPGameModeBase::ToggleMouseCursor(bool boolean)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = boolean;
	PlayerController->bEnableClickEvents = boolean;

	if (boolean)
	{
		FInputModeUIOnly FInputMode;
		PlayerController->SetInputMode(FInputMode);
	}
	else
	{
		FInputModeGameOnly FInputMode;
		PlayerController->SetInputMode(FInputMode);
	}
}

bool AMyGC_UE4CPPGameModeBase::IsWin()
{
	return bPlayerWon;
}

bool AMyGC_UE4CPPGameModeBase::IsLoose()
{
	return bPlayerLost;
}

