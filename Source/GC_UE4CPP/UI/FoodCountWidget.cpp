// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodCountWidget.h"

UFoodCountWidget::UFoodCountWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	CurrentValue = 0;
}

void UFoodCountWidget::UpdateFoodCount(int32 Value)
{
	if(FoodTxt && FoodBar)
	{
		CurrentValue+=Value;
		if (CurrentValue > 5) {CurrentValue--;}
		if (CurrentValue < 0) {CurrentValue++;}
		
		FoodBar->SetPercent((static_cast<float>(CurrentValue)/100)*20);
		FoodTxt->SetText(FText::FromString(FString::FromInt(CurrentValue) + "/5"));
	}
}

void UFoodCountWidget::ResetCount()
{
	FoodBar->SetPercent(0.0f);
	FoodTxt->SetText(FText::FromString("0/5"));
}