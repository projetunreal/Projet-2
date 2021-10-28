// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

class UMainMenuWidget;
/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AMainMenuGameModeBase final : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void virtual BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:
	UMainMenuWidget* MainMenuWidget;
};
