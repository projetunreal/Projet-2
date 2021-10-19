// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FoodCountWidget.h"

#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateFoodCount(int32 Value);

	UFUNCTION()
	void ResetCount();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> FoodCountWidgetClass;

private:
	UFoodCountWidget* FoodCountWidget;
	
};
