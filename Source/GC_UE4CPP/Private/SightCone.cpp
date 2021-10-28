// Fill out your copyright notice in the Description page of Project Settings.


#include "SightCone.h"
#include "AICharacter.h"

// Sets default values
ASightCone::ASightCone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProcMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
}

// Called when the game starts or when spawned
void ASightCone::BeginPlay()
{
	Super::BeginPlay();

	CollisionParams.AddIgnoredActor(AICharacter);
}

// Called every frame
void ASightCone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InitMesh();

	if (!AICharacter) return;

	FVector const UpVector = GetActorUpVector();
	FVector const EyeLocation = GetActorLocation() + UpVector * AICharacter->GetEyeHeightFromCenter();
	FVector RayGlobalVector = GetActorForwardVector().RotateAngleAxis(-VisionAngle, UpVector);
	FVector RayLocalVector = FVector(1.0f, 0.0f, 0.0f).RotateAngleAxis(-VisionAngle, UpVector);

	AddDetectedVertice(EyeLocation, RayGlobalVector, RayLocalVector);

	float StepAngle = 2 * VisionAngle / (RayAmount-1);
	for (int i = 2; i <= RayAmount; i++)
	{
		RayGlobalVector = RayGlobalVector.RotateAngleAxis(StepAngle, UpVector);
		RayLocalVector = RayLocalVector.RotateAngleAxis(StepAngle, UpVector);

		AddDetectedVertice(EyeLocation, RayGlobalVector, RayLocalVector);

		Triangles.Add(0);
		Triangles.Add(i);
		Triangles.Add(i-1);
	}

	ProcMeshComp->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, false);
}

void ASightCone::OnConstruction(const FTransform& Transform)
{
	ClearMeshData();

	//Function that creates mesh section
	ProcMeshComp->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, false);
	if (Material)
	{
		ProcMeshComp->SetMaterial(0, Material);
	}
}

void ASightCone::ClearMeshData()
{
	Vertices.Empty();
	Normals.Empty();
	Triangles.Empty();
	UVs.Empty();
	VertexColors.Empty();
	Tangents.Empty();
}

void ASightCone::InitMesh()
{
	ClearMeshData();

	Vertices.Add(DisplayLocationFromCenter);

	Normals.Init(FVector(0.0f, 0.0f, 1.0f), RayAmount + 1);
	VertexColors.Init(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), RayAmount + 1);
	Tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), RayAmount + 1);
}

void ASightCone::AddDetectedVertice(FVector const EyeLocation, FVector RayGlobalVector, FVector RayLocalVector)
{
	FHitResult OutHit;
	float Distance;

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, EyeLocation, EyeLocation + RayGlobalVector * SightRadius, ECC_Visibility, CollisionParams);

	Distance = bHit ? OutHit.Distance : SightRadius;

	Vertices.Add(DisplayLocationFromCenter + RayLocalVector * Distance);
}

