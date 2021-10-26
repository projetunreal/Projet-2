// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "SightCone.h"
#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters p;
	p.Owner = this;
	SightCone = GetWorld()->SpawnActor<ASightCone>(SightConeBP, GetActorLocation(), GetActorRotation(), p);
	SightCone->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SightCone->SetAICharacter(this);

	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());
	if (!EnemyAIController) return;

	UAIPerceptionComponent* AIPerceptionComponent = EnemyAIController->GetAIPerceptionComponent();
	if (!AIPerceptionComponent) return;

	UAISenseConfig_Sight* AISenseConfig = Cast<UAISenseConfig_Sight>(AIPerceptionComponent->GetSenseConfig(UAISense::GetSenseID<UAISense_Sight>()));
	if (!AISenseConfig) return;

	SightCone->SetSightRadius(AISenseConfig->SightRadius);
	SightCone->SetVisionAngle(AISenseConfig->PeripheralVisionAngleDegrees);
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::DestroySightCone()
{
	SightCone->Destroy();
}
