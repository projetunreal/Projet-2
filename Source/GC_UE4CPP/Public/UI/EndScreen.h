// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Components/Button.h"

#include "EndScreen.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UEndScreen final : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnClickButton();

	UFUNCTION()
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayAgainButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* WinLoseTextBlock;
};
