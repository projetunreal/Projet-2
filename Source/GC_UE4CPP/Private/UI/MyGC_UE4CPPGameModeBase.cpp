// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyGC_UE4CPPGameModeBase.h"

#include "UI/FoodCountWidget.h"

void AMyGC_UE4CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ToggleMouseCursor(false);

	//Widget Spawn
	if(FoodCountWidgetClass)
	{
		FoodCountWidget = CreateWidget<UFoodCountWidget>(GetWorld(), FoodCountWidgetClass);
		if (FoodCountWidget)
		{
			FoodCountWidget->AddToViewport();
		}
	}
}

void AMyGC_UE4CPPGameModeBase::WinGame()
{
	//Avoid duplicate spawn
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
			if (Text)
			{
				Text->SetText(FText::FromString("You won!"));
				Text->SetJustification(ETextJustify::Center);
				Text->SetColorAndOpacity(FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f)));
			}
		}
	}
}

void AMyGC_UE4CPPGameModeBase::LoseGame()
{
	//Avoid duplicate spawn
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
			if (Text)
			{
				Text->SetText(FText::FromString("You lost!"));
				Text->SetJustification(ETextJustify::Center);
				Text->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f)));
			}
		}
	}
}

void AMyGC_UE4CPPGameModeBase::PauseGame()
{
	//Avoid duplicate spawn
	if (bGamePaused) {return;}
	
	//Widget spawn
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
		if (PauseWidget)
		{
			bGamePaused = true;
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (!PlayerController) { return; }

			//Pause locally
			PlayerController->SetPause(bGamePaused);

			ToggleMouseCursor(true);

			//Add Pause Screen
			PauseWidget->AddToViewport();
			
			UTextBlock* Text = PauseWidget->PauseTextBlock;
			if (Text)
			{
				Text->SetText(FText::FromString("PAUSE"));
				Text->SetJustification(ETextJustify::Center);
			}
	
			UImage* BackgroundImage = PauseWidget->BackgroundImage;
			if (BackgroundImage)
			{
				BackgroundImage->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.5f, 0.1f));
			}
		}
	}
}

void AMyGC_UE4CPPGameModeBase::UnpauseGame()
{
	bGamePaused = false;
	PauseWidget->RemoveFromViewport();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetPause(bGamePaused);
	}

	ToggleMouseCursor(false);
}

void AMyGC_UE4CPPGameModeBase::ToggleMouseCursor(const bool Boolean) const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) {return;}

	PlayerController->bShowMouseCursor = Boolean;
	PlayerController->bEnableClickEvents = Boolean;

	if (Boolean)
	{
		const FInputModeUIOnly FInputMode;
		PlayerController->SetInputMode(FInputMode);
	}
	else
	{
		const FInputModeGameOnly FInputMode;
		PlayerController->SetInputMode(FInputMode);
	}
}

void AMyGC_UE4CPPGameModeBase::TogglePlayerInput(const bool Boolean) const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) {return;}

	if (Boolean)
	{
		PlayerController->GetPawn()->EnableInput(PlayerController);
	}
	else
	{
		PlayerController->GetPawn()->DisableInput(PlayerController);
	}
}

void AMyGC_UE4CPPGameModeBase::UpdateFoodCount(const int32 Value) const
{
	if(FoodCountWidget)
	{
		FoodCountWidget->UpdateFoodCount(Value);
	}
}

bool AMyGC_UE4CPPGameModeBase::IsWin() const
{
	return bPlayerWon;
}

bool AMyGC_UE4CPPGameModeBase::IsLose() const
{
	return bPlayerLost;
}