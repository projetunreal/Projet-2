// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodUserActor.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class GC_UE4CPP_API AMyCharacter final : public AFoodUserActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
		FTransform CharacterFeetPos;
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Chair;
	
	UFUNCTION()
		virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	// Sets default values for this character's properties
	AMyCharacter();

	void MoveRight(const float Axis);
	void MoveForward(const float Axis);
	void ZoomCamera(const float Axis);

	
	bool IsSit() const;
	UFUNCTION()
	void PauseGame();


	// Called to bind functionality to input
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InteractWithObject();
private :
	
	const float ZoomIncrement = 60;
	const float ZoomMax = 500;
	const float InteractRange = 500;

	void SitOnChair(const AActor* Chair);
	void StandUp();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};