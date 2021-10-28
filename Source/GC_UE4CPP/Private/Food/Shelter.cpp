// Fill out your copyright notice in the Description page of Project Settings.

#include "Food/Shelter.h"
#include "Food/FoodHandler.h"
#include "Food/Food.h"

#include "UI/MyGC_UE4CPPGameModeBase.h"
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
		AFoodUserActor* Actor = Food->GetFoodUserActor();
		if (Actor) Actor->DropFood();

		Food->Destroy();

		const AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) {return;}
		GameMode->UpdateFoodCount(1);
	}
}

