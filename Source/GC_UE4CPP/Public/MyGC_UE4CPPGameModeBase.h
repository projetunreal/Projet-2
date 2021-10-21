// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GC_UE4CPPGameModeBase.h"
#include "Components/WidgetComponent.h"
#include "../UI/EndScreen.h"
#include "GC_UE4CPP/UI/PauseWidget.h"

#include "MyGC_UE4CPPGameModeBase.generated.h"

class UFoodCountWidget;
/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AMyGC_UE4CPPGameModeBase : public AGC_UE4CPPGameModeBase
{
	GENERATED_BODY()

protected:
	
	bool bPlayerWon;
	bool bPlayerLost;
	bool bGamePaused;
	
public:
	AMyGC_UE4CPPGameModeBase();
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void WinGame();

	UFUNCTION()
	void LoseGame();

	UFUNCTION()
	void PauseGame();

	void UnpauseGame();
	void ToggleMouseCursor(bool boolean);
	void TogglePlayerInput(bool boolean);

	UFUNCTION()
	void UpdateFoodCount(int32 Value);
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> EndScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> FoodCountWidgetClass;
	
	bool IsWin();
	bool IsLoose();
private:
	UEndScreen* EndScreenWidget;
	UPauseWidget* PauseWidget;
	UFoodCountWidget* FoodCountWidget;
};
