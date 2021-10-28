// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacter.h"
#include "AI/AICharacter.h"
#include "Food/Food.h"
#include "Food/FoodSpot.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/MyGC_UE4CPPGameModeBase.h"


void AMyCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
const bool bSelfMoved, const FVector HitLocation, const FVector HitNormal, const FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (Other->GetClass()->IsChildOf(AAICharacter::StaticClass()))
	{
		AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) {return;}
		
		GameMode->LoseGame();
	}
}

// Sets default values
AMyCharacter::AMyCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (!CharMovement)	return;
	
	CharMovement->bOrientRotationToMovement = true;
	CharMovement->RotationRate = FRotator(0.0f, 700.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("CameraBoom")));
	if (!CameraBoom) return;
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	if (!Camera) return;
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay(); 
	if (!GetMesh()) { return; }
	CharacterFeetPos = GetMesh()->GetRelativeTransform();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!PlayerInputComponent) return;
	PlayerInputComponent->BindAxis("Horizontal", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Vertical", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Zoom", this, &AMyCharacter::ZoomCamera);
	
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::PauseGame);

	PlayerInputComponent->BindAction("Interact", IE_Pressed,this, &AMyCharacter::InteractWithObject);
}

void AMyCharacter::MoveRight(const float Axis)
{
	if (!Controller) return;
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis );
}

void AMyCharacter::MoveForward(const float Axis)
{
	if (!Controller) return;
	const FRotator Rotation = Controller->GetControlRotation(); 
	const FRotator YawRotation(0, Rotation.Yaw, 0); 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction , Axis);
}

void AMyCharacter::ZoomCamera(const float Axis)
{
	if (!IsSit() && CameraBoom && CameraBoom->TargetArmLength + Axis * ZoomIncrement > 0 && CameraBoom->TargetArmLength + Axis * ZoomIncrement < ZoomMax)
		CameraBoom->TargetArmLength += Axis * ZoomIncrement;
}

void AMyCharacter::PauseGame()
{
	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) {return;}
	
	GameMode->PauseGame();
}

bool AMyCharacter::IsSit() const
{
	return Chair != nullptr;
}

void AMyCharacter::InteractWithObject()
{
	FHitResult OutHit;
	if (!Camera) {return;}
	FVector Start = Camera->GetComponentLocation();
	FVector ForwardVec = Camera->GetForwardVector();

	if (!CameraBoom) { return; }
	Start += (ForwardVec * CameraBoom->TargetArmLength);
	FVector End = Start + (ForwardVec * InteractRange);
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	AActor* OtherActor = OutHit.GetActor();
	
	if (Chair) 
		StandUp();
	else if (bHit && OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(AFoodSpot::StaticClass()))
			if (FoodHeld)
				PutFoodOnSpot(Cast<AFoodSpot>(OtherActor));
			else
				PickUpFoodFromSpot(Cast<AFoodSpot>(OtherActor));
		
		else if (OtherActor->GetClass()->IsChildOf(AFood::StaticClass()))
			PickUpFood(Cast<AFood>(OtherActor));

		else if (OtherActor->ActorHasTag("Chair"))
			SitOnChair(OtherActor);
		else if (FoodHeld)
			DropFood();
	}
	else if (FoodHeld)
		DropFood();
}
void AMyCharacter::SitOnChair(const AActor* NewChair)
{
	if (!GetController()) {return;}
	GetController()->SetIgnoreMoveInput(true);
	
	if (!GetMesh()) {return;}
	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->SetCollisionProfileName(TEXT("OverlapAll"));

	GetMesh()->AttachToComponent(Cast<AStaticMeshActor >(NewChair)->GetStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SitSocket"));

	if (!GetCapsuleComponent()) {return;}
	GetCapsuleComponent()->AttachToComponent(Cast<AStaticMeshActor >(NewChair)->GetStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SitSocket"));
	CameraBoom->bUsePawnControlRotation = false;
	const FRotator NewRotation = FRotator(0.0, 270.0, 0.0);
	CameraBoom->SetRelativeRotation(NewRotation, false);
	this->Chair = Cast<AStaticMeshActor>(NewChair)->GetStaticMeshComponent();
}
void AMyCharacter::StandUp()
{
	if (!GetController()) { return; }
	GetController()->SetIgnoreMoveInput(false);
	GetCapsuleComponent()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

	if (!GetMesh()) { return; }
	GetMesh()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

	if (!GetCapsuleComponent()) { return; }
	GetCapsuleComponent()->AttachToComponent(Chair, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeaveSocket"));
	GetMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeaveSocket"));

	GetMesh()->SetRelativeTransform(CharacterFeetPos);
	
	GetCapsuleComponent()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	CameraBoom->bUsePawnControlRotation = true;
	Chair = nullptr;
}