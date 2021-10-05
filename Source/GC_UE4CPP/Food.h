// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

UCLASS()
class GC_UE4CPP_API AFood : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Sm;

public:
	// Sets default values for this actor's properties
	AFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PickedUp();
};