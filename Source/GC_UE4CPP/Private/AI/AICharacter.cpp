// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/SightCone.h"
#include "AI/EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters p;
	p.Owner = this;

	SightCone = GetWorld()->SpawnActor<ASightCone>(SightConeBP, GetActorLocation(), GetActorRotation(), p);
	if (!SightCone) return;

	SightCone->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());
	if (!EnemyAIController) return;

	UAIPerceptionComponent* AIPerceptionComponent = EnemyAIController->GetAIPerceptionComponent();
	if (!AIPerceptionComponent) return;

	UAISenseConfig_Sight* AISenseConfig = Cast<UAISenseConfig_Sight>(AIPerceptionComponent->GetSenseConfig(UAISense::GetSenseID<UAISense_Sight>()));
	if (!AISenseConfig) return;

	SightCone->InitCone(AISenseConfig->SightRadius, AISenseConfig->PeripheralVisionAngleDegrees, EyesLocationFromCenter, this);
}


void AAICharacter::DestroySightCone() const
{
	SightCone->Destroy();
}
