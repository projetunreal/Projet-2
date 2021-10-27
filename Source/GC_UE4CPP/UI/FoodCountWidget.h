// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "FoodCountWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UFoodCountWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UFoodCountWidget(const FObjectInitializer& ObjectInitializer);
	
	void UpdateFoodCount(int32 Value);

	void ResetCount() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* FoodHUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* FoodBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FoodTxt;

protected:
	int32 CurrentValue;
};
