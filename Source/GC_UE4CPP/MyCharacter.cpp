// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

void AMyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Food"))
	{
		FoodHeld = Cast<AFood>(OtherActor);
		FoodHeld->PickedUp();
		FName socketFood = TEXT("FoodSocket");
		UE_LOG(LogTemp, Warning, TEXT("Test"));
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);

		OtherActor->AttachToActor(this, rules, socketFood);
		//OtherActor->K2_AttachToActor(this, OtherActor->GetAttachParentSocketName(), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	}
}

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("CameraBoom")));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bEnableCameraLag = true;
	//CameraBoom->bDrawDebugLagMarkers = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	SM_Character = GetMesh();
	TriggerCapsule = GetCapsuleComponent();
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraBoom->TargetArmLength = 300.0f;

	CameraBoom->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Vertical", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Zoom", this, &AMyCharacter::ZoomCamera);
}

void AMyCharacter::MoveRight(float axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, axis);
}

void AMyCharacter::MoveForward(float axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, axis);
}

void AMyCharacter::ZoomCamera(float axis)
{
	if (CameraBoom->TargetArmLength + axis * ZOOM_INCREMENT > 0 && CameraBoom->TargetArmLength + axis * ZOOM_INCREMENT < ZOOM_MAX)
		CameraBoom->TargetArmLength += axis * ZOOM_INCREMENT;
}
