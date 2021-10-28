// Fill out your copyright notice in the Description page of Project Settings.


#include "Food/FoodHandler.h"
#include "Food/Food.h"


void AFoodHandler::AddFood(AFood* Food)
{
	Foods.Add(Food);
}

void AFoodHandler::Remove(AFood* Food)
{
	Foods.RemoveSwap(Food);
}

