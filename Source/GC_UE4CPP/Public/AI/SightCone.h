// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

#include "SightCone.generated.h"

class AAICharacter;

UCLASS()
class GC_UE4CPP_API ASightCone final : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* ProcMeshComp;

	UPROPERTY()
		TArray<FVector> Vertices;
	UPROPERTY()
		TArray<FVector> Normals;
	UPROPERTY()
		TArray<int32> Triangles;
	UPROPERTY()
		TArray<FVector2D> UVs;
	UPROPERTY()
		TArray<FLinearColor> VertexColors;
	UPROPERTY()
		TArray<FProcMeshTangent> Tangents;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;
	UPROPERTY(EditAnywhere)
		FVector DisplayLocationFromCenter = FVector(0.0f, 0.0f, -80.0f);
	UPROPERTY(EditAnywhere)
		int RayAmount = 50;

	float SightRadius;

	float VisionAngle;

	FVector EyesLocationFromCenter;

	FCollisionQueryParams CollisionParams;

public:	
	// Sets default values for this actor's properties
	ASightCone();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	void ClearMeshData();

	void InitMesh();
	void InitCone(float SomeSightRadius, float SomeVisionAngle, FVector SomeEyesLocationFromCenter, AAICharacter* SomeAIChar);

	void AddDetectedVertice(FVector const EyeLocation, FVector RayGlobalVector, FVector RayLocalVector);
};
