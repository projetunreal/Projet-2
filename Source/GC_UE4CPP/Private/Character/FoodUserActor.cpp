// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FoodUserActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Food/FoodSpot.h"
#include "Food/Food.h"

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

void AFoodUserActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FoodHeld)
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed / 2;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	}
}

void AFoodUserActor::BeginPlay()
{
	Super::BeginPlay();

	BaseSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AFoodUserActor::PickUpFood(AFood* Food)
{
	if (!FoodHeld)
	{
		FoodHeld = Food;
		FoodHeld->GetMesh()->SetSimulatePhysics(false);
		FoodHeld->GetMesh()->SetCollisionProfileName(TEXT("OverlapAll"));
		FoodHeld->GetBox()->SetCollisionProfileName(TEXT("IgnoreAll"));
		FoodHeld->GetMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodHeld->SetOnFloor(false);
		FoodHeld->SetFoodUserActor(this);
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
		FoodHeld->GetMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		Spot->SetFood(nullptr);
		FoodHeld->SetOnFloor(false);
		FoodHeld->SetFoodUserActor(this);
	}
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
		FoodHeld->GetMesh()->AttachToComponent(Spot->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("FoodSocket"));
		FoodHeld->SetOnFloor(false);
		FoodHeld->SetFoodUserActor(nullptr);
		FoodHeld = nullptr;

	}
}

bool AFoodUserActor::IsHoldingFood() const
{
	return FoodHeld != nullptr;
}

void AFoodUserActor::DropFood()
{
	if (FoodHeld)
	{
		FoodHeld->GetMesh()->SetSimulatePhysics(true);
		FoodHeld->GetMesh()->SetCollisionProfileName(TEXT("FoodDroped"));
		FoodHeld->GetBox()->SetCollisionProfileName(TEXT("FoodBox"));
		FoodHeld->GetMesh()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		FoodHeld->SetOnFloor(true);
		FoodHeld->SetFoodUserActor(nullptr);
		FoodHeld = nullptr;
	}
}
