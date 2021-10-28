// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UPauseWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnClickButton();

	UFUNCTION()
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PauseTextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* BackgroundImage;
};
