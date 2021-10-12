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
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Sets default values for this character's properties
	AMyCharacter();

	void MoveRight(float axis);
	void MoveForward(float axis);
	void ZoomCamera(float axis);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FoodAction();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
