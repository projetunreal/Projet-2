// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodHandler.h"
#include "Food.h"


void AFoodHandler::AddFood(AFood* Food)
{
	Foods.Add(Food);
}

void AFoodHandler::Remove(AFood* Food)
{
	Foods.RemoveSwap(Food);
}

