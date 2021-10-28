// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FoodCountWidget.h"

#include "UI/MyGC_UE4CPPGameModeBase.h"

UFoodCountWidget::UFoodCountWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	CurrentValue = 0;
}

void UFoodCountWidget::UpdateFoodCount(const int32 Value)
{
	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) {return;}
	
	if(FoodTxt && FoodBar)
	{
		CurrentValue+=Value;
		
		if (CurrentValue > 5) {CurrentValue--;}
		if (CurrentValue < 0) {CurrentValue++;}
		
		FoodBar->SetPercent((static_cast<float>(CurrentValue)/100)*20);
		FoodTxt->SetText(FText::FromString(FString::FromInt(CurrentValue) + "/5"));

		if (CurrentValue >= 5)
		{
			GameMode->WinGame();
		}
	}
}

void UFoodCountWidget::ResetCount() const
{
	FoodBar->SetPercent(0.0f);
	FoodTxt->SetText(FText::FromString("0/5"));
}
