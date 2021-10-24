// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodUserActor.h"

// Sets default values
AFoodUserActor::AFoodUserActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called to bind functionality to input
void AFoodUserActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AFoodUserActor::PickUpFood(AFood* Food)
{
	if (!FoodHeld)
	{
		FoodHeld = Food;
		FoodHeld->GetMesh()->SetSimulatePhysics(false);
		FoodHeld->GetMesh()->SetCollisionProfileName(TEXT("OverlapAll"));
		FoodHeld->GetBox()->SetCollisionProfileName(TEXT("IgnoreAll"));
		FName socketFood = TEXT("FoodSocket");
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		FoodHeld->GetMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodHeld->SetOnFloor(false);
	}
}
void AFoodUserActor::PickUpFoodFromSpot(AFoodSpot* Spot)
{
	if (Spot->IsFoodOn())
	{
		FoodHeld = Spot->GetFood();
		FoodHeld->GetMesh()->SetSimulatePhysics(false);
		FoodHeld->GetMesh()->SetCollisionProfileName(TEXT("OverlapAll"));
		FoodHeld->GetBox()->SetCollisionProfileName(TEXT("IgnoreAll"));
		FName socketFood = TEXT("FoodSocket");
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		FoodHeld->GetMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		Spot->SetFood(nullptr);
		FoodHeld->SetOnFloor(false);
	}
}
AFood* AFoodUserActor::GetFood()
{
	return FoodHeld;
}
void AFoodUserActor::PutFoodOnSpot(AFoodSpot* Spot)
{
	if ( FoodHeld && !Spot->IsFoodOn() )
	{
		FoodHeld->GetMesh()->SetSimulatePhysics(false);
		FoodHeld->GetMesh()->SetCollisionProfileName(TEXT("IgnoreAll"));
		FoodHeld->GetBox()->SetCollisionProfileName(TEXT("IgnoreAll"));
		FoodHeld->GetMesh()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		Spot->SetFood(FoodHeld);
		FoodHeld->GetMesh()->AttachToComponent(Spot->getMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodHeld = nullptr;
	}
}
bool AFoodUserActor::IsHoldingFood()
{
	return FoodHeld != nullptr;
}
void AFoodUserActor::DropFood()
{
	if (FoodHeld)
	{

		FoodHeld->GetMesh()->SetSimulatePhysics(true);
		FoodHeld->GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
		FoodHeld->GetBox()->SetCollisionProfileName(TEXT("FoodBox"));
		FoodHeld->GetMesh()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		FoodHeld = nullptr;
	}
}
