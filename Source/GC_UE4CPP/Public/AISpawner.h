// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AICharacter.h"

#include "AISpawner.generated.h"

UCLASS()
class GC_UE4CPP_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawner();
	
	UPROPERTY(EditAnywhere)
		float DestroyRadius = 150;

	UPROPERTY(EditAnywhere)
		float RespawnMinCooldown = 0;

	UPROPERTY(EditAnywhere)
		float RespawnMaxCooldown = 5;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AAICharacter> AICharacterBP;

private:

	int AICount;

	TArray<AAICharacter*> SpawnedAI;

	float BeginTime;
	TArray<float> RespawnTimes;

	void SpawnIA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
