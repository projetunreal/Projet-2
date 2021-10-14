// Fill out your copyright notice in the Description page of Project Settings.


#include "Shelter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AShelter::AShelter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));

	
}

// Called when the game starts or when spawned
void AShelter::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetVisibility(false);

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AShelter::AShelter::OnStaticMeshBeginOverlap);
}

// Called every frame
void AShelter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShelter::OnStaticMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass()))
	{
		OtherActor->Destroy();
		
		AInGameHUD* HUD = Cast<AInGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		HUD->UpdateFoodCount(1);
		
		//TODO: Change current animation
	}
	else if(OtherActor->GetClass()->IsChildOf(AFoodUserActor::StaticClass()))
	{
		Cast<AFoodUserActor>(OtherActor)->DropFood();
	}
}

