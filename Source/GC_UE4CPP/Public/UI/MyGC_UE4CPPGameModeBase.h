// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GC_UE4CPPGameModeBase.h"
#include "Components/WidgetComponent.h"
#include "UI/EndScreen.h"
#include "UI/PauseWidget.h"

#include "MyGC_UE4CPPGameModeBase.generated.h"

class UFoodCountWidget;
/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AMyGC_UE4CPPGameModeBase final : public AGC_UE4CPPGameModeBase
{
	GENERATED_BODY()

protected:
	bool bPlayerWon = false;
	bool bPlayerLost = false;
	bool bGamePaused = false;
	
public:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void WinGame();

	UFUNCTION()
	void LoseGame();

	UFUNCTION()
	void PauseGame();
	void UnpauseGame();
	
	void ToggleMouseCursor(bool Boolean) const;
	void TogglePlayerInput(bool Boolean) const;
	
	bool IsWin() const;
	bool IsLose() const;

	UFUNCTION()
	void UpdateFoodCount(int32 Value) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> EndScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> FoodCountWidgetClass;
	
private:
	UEndScreen* EndScreenWidget;
	UPauseWidget* PauseWidget;
	UFoodCountWidget* FoodCountWidget;
};
