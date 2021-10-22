// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"

#include "MyGC_UE4CPPGameModeBase.h"

class AMyGC_UE4CPPGameModeBase;

void UPauseWidget::OnClickButton()
{
	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
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