// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"

#include "UI/MyGC_UE4CPPGameModeBase.h"

void UPauseWidget::OnClickButton()
{
	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) {return;}
	GameMode->UnpauseGame();	
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClickButton);
	}
}
