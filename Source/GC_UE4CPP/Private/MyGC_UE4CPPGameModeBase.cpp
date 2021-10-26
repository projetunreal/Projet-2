// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGC_UE4CPPGameModeBase.h"

#include "GC_UE4CPP/UI/FoodCountWidget.h"

AMyGC_UE4CPPGameModeBase::AMyGC_UE4CPPGameModeBase()
{
	
}

void AMyGC_UE4CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ToggleMouseCursor(false);
	
	if(FoodCountWidgetClass)
	{
		FoodCountWidget = CreateWidget<UFoodCountWidget>(GetWorld(), FoodCountWidgetClass);
		if (FoodCountWidget)
		{
			FoodCountWidget->AddToViewport();
		}
	}
	
	bGamePaused = false;
	
}

void AMyGC_UE4CPPGameModeBase::WinGame()
{
	if (bPlayerLost || bPlayerWon) {return;}
	
	//Change animation and AI behavior
	bPlayerWon = true;
	
	TogglePlayerInput(false);
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
	
	//Change animation and AI behavior
	bPlayerLost = true;

	TogglePlayerInput(false);
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

void AMyGC_UE4CPPGameModeBase::TogglePlayerInput(bool boolean)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (boolean)
	{
		PlayerController->GetPawn()->EnableInput(PlayerController);
	}
	else
	{
		PlayerController->GetPawn()->DisableInput(PlayerController);
	}
}

void AMyGC_UE4CPPGameModeBase::UpdateFoodCount(int32 Value)
{
	if(FoodCountWidget)
	{
		FoodCountWidget->UpdateFoodCount(Value);
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

