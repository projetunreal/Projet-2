// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodUserActor.h"

// Sets default values
AFoodUserActor::AFoodUserActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodUserActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodUserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFoodUserActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AFoodUserActor::PickUpFood(AFood* food)
{
	if (!FoodHeld)
	{
		FoodHeld = food;
		//FoodHeld->PickedUp();
		FoodHeld->StaticMesh->SetSimulatePhysics(false);
		FoodHeld->StaticMesh->SetCollisionProfileName(TEXT("OverlapAll"));
		FName socketFood = TEXT("FoodSocket");
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		FoodHeld->StaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
	}
}
void AFoodUserActor::PickUpFoodFromSpot(AFoodSpot* spot)
{
	if (spot->IsFoodOn())
	{
		
		FoodHeld = spot->GetFood();
		FoodHeld->StaticMesh->SetSimulatePhysics(false);
		FoodHeld->StaticMesh->SetCollisionProfileName(TEXT("OverlapAll"));
		FName socketFood = TEXT("FoodSocket");
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		FoodHeld->StaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		spot->SetFood(nullptr);
	}
}
void AFoodUserActor::FoodAction()
{
  //placeHolder Might get removed
}
void AFoodUserActor::PutFoodOnSpot(AFoodSpot* spot)
{
	if ( FoodHeld && !spot->IsFoodOn() )
	{
		FoodHeld->StaticMesh->SetSimulatePhysics(false);
		FoodHeld->StaticMesh->SetCollisionProfileName(TEXT("IgnoreAll"));

		FoodHeld->StaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		spot->SetFood(FoodHeld);
		FoodHeld->StaticMesh->AttachToComponent(spot->getMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodHeld = nullptr;
	}
}
bool AFoodUserActor::IsHoldingFood()
{
	return FoodHeld !=nullptr;
}
void AFoodUserActor::DropFood()
{
	if (FoodHeld)
	{

		FoodHeld->StaticMesh->SetSimulatePhysics(true);
		FoodHeld->StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));

		FoodHeld->StaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		FoodHeld = nullptr;
	}
}
