// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

AInGameHUD::AInGameHUD()
{
	
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if(FoodCountWidgetClass)
	{
		FoodCountWidget = CreateWidget<UFoodCountWidget>(GetWorld(), FoodCountWidgetClass);
		if (FoodCountWidget)
		{
			FoodCountWidget->AddToViewport();
		}
	}
}

void AInGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHUD::UpdateFoodCount(int32 Value)
{
	if(FoodCountWidget)
	{
		FoodCountWidget->UpdateFoodCount(Value);
	}
}

void AInGameHUD::ResetCount()
{
	if(FoodCountWidget)
	{
		FoodCountWidget->ResetCount();
	}
}

