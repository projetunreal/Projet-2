// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Food.h"
#include "FoodUser.generated.h"
/**
 * 
 */
UINTERFACE(BlueprintType)
class  GC_UE4CPP_API UFoodUser : public UInterface
{
	GENERATED_BODY()
};
class GC_UE4CPP_API IFoodUser 
{
	GENERATED_BODY()
public:
	virtual void PickUpFood(AFood* food);
	virtual void DropFood();
};
