// Fill out your copyright notice in the Description page of Project Settings.

#include "Shelter.h"
#include "FoodHandler.h"
#include "Food.h"

#include "MyGC_UE4CPPGameModeBase.h"

// Sets default values
AShelter::AShelter()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
}

// Called when the game starts or when spawned
void AShelter::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetVisibility(false);

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AShelter::AShelter::OnStaticMeshBeginOverlap);
}

void AShelter::OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFood* Food = Cast<AFood>(OtherActor);
	if(Food)
	{
		AFoodHandler* FoodHandler = Food->GetFoodHandler();
		if (FoodHandler)
		{
			FoodHandler->Remove(Food);
		}
		Food->Destroy();

		const AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->UpdateFoodCount(1);
	}

	AFoodUserActor* FoodUser = Cast<AFoodUserActor>(OtherActor);
	if(FoodUser)
	{
		FoodUser->DropFood();
	}
}

