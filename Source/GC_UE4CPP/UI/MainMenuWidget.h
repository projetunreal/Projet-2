// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UMainMenuWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void OnClickPlayButton();
	
	UFUNCTION()
	void OnClickQuitButton();

	UFUNCTION()
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;
};
