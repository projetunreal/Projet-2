// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Food.h"
#include "FoodSpot.h"

#include "FoodUserActor.h"
#include "MyCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API AMyCharacter : public AFoodUserActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		UCapsuleComponent* TriggerCapsule;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SC_Scene;
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;


	UPROPERTY(VisibleAnywhere)
		float ZOOM_INCREMENT = 60;
	UPROPERTY(VisibleAnywhere)
		float ZOOM_MAX = 500;

	UFUNCTION()
		virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	// Sets default values for this character's properties
	AMyCharacter();

	void MoveRight(float axis);
	void MoveForward(float axis);
	void ZoomCamera(float axis);

	void MoveCameraRight(float axis);
	void MoveCameraDown(float axis);
	bool IsSit();
	UFUNCTION()
	void PauseGame();
	//void PlusReleased();
	//UFUNCTION()
	//void MinusReleased();



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FoodAction();
private :
	bool bSit = false;
};
