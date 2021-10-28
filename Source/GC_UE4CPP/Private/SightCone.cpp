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
	VisionAngle = 20.0f;
}

// Called every frame
void ASightCone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClearMeshData();

	if (!AICharacter) return;

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(AICharacter);

	FVector const UpVector = GetActorUpVector();
	FVector RayGlobalVector = GetActorForwardVector().RotateAngleAxis(-VisionAngle, UpVector);
	FVector RayLocalVector = FVector(1.0f, 0.0f, 0.0f).RotateAngleAxis(-VisionAngle, UpVector);
	FVector const EyeLocation = GetActorLocation() + UpVector * AICharacter->GetEyeHeightFromCenter();
	FVector const DisplayLocation = FVector(0.0f, 0.0f, DisplayHeightFromCenter);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, EyeLocation, EyeLocation + RayGlobalVector * SightRadius, ECC_Visibility, CollisionParams);
	float Distance;
	if (bHit)
	{
		Distance = OutHit.Distance;
	}
	else
	{
		Distance = SightRadius;
	}

	Vertices.Add(DisplayLocation);
	Vertices.Add(DisplayLocation + RayLocalVector * Distance);

	float StepAngle = 2 * VisionAngle / (RayAmount-1);
	for (int i = 2; i <= RayAmount; i++)
	{
		RayGlobalVector = RayGlobalVector.RotateAngleAxis(StepAngle, UpVector);
		RayLocalVector = RayLocalVector.RotateAngleAxis(StepAngle, UpVector);

		bHit = GetWorld()->LineTraceSingleByChannel(OutHit, EyeLocation, EyeLocation + RayGlobalVector * SightRadius, ECC_Visibility, CollisionParams);
		if (bHit)
		{
			Distance = OutHit.Distance;
		}
		else
		{
			Distance = SightRadius;
		}
		Vertices.Add(DisplayLocation + RayLocalVector * Distance);

		Triangles.Add(0);
		Triangles.Add(i);
		Triangles.Add(i-1);
	}

	Normals.Init(FVector(0.0f, 0.0f, 1.0f), RayAmount + 1);
	VertexColors.Init(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), RayAmount + 1);
	Tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), RayAmount + 1);

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

