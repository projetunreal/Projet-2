// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AISpawner.generated.h"

class AAICharacter;
class AFoodSpotHandler;
class AFoodHandler;
class AFood;


UCLASS()
class GC_UE4CPP_API AAISpawner final : public AActor
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(EditAnywhere)
		float DestroyRadius = 150;

	UPROPERTY(EditAnywhere)
		float RespawnMinCooldown = 0;

	UPROPERTY(EditAnywhere)
		float RespawnMaxCooldown = 5;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AAICharacter> AICharacterBP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AFood> FoodBP;

	UPROPERTY(EditAnywhere)
		AFoodSpotHandler* FoodSpotHandler;

	UPROPERTY(EditAnywhere)
		AFoodHandler* FoodHandler;

	int AICount;

	TArray<AAICharacter*> SpawnedAI;

	float BeginTime;
	TArray<float> RespawnTimes;

	void SpawnIa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AAISpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
