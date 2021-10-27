// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "AICharacter.h"
#include "Food.h"
#include "FoodSpot.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyGC_UE4CPPGameModeBase.h"

 void AMyCharacter::Tick(float DeltaSeconds)
{
	 const FRotator Rotation = Controller->GetControlRotation();
	 const FRotator YawRotation(0, Rotation.Yaw, 0);
	 float Modifier = (FoodHeld != nullptr) ? 0.5f : 1.0f;
	 //if (InputDirection.X + InputDirection.Y == 2)
	 {
	//	 InputDirection.X = 0.5;
	//	 InputDirection.Y = 0.5;
	 }	 
	 FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * InputDirection.Y;
	 Direction += FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * InputDirection.X;
	 AddMovementInput(Direction, Modifier);
	 InputDirection.X = 0;
	 InputDirection.Y = 0;
}

void AMyCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (Other->GetClass()->IsChildOf(AAICharacter::StaticClass()))
	{
		AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->LoseGame();
	}
}

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 700.0f, 0.0f);
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("CameraBoom")));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bEnableCameraLag = true;
	//CameraBoom->bDrawDebugLagMarkers = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay(); 
	CharacterFeetPos = GetMesh()->GetRelativeTransform();
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
	
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::PauseGame);

	PlayerInputComponent->BindAction("Interact", IE_Pressed,this, &AMyCharacter::InteractWithObject);
}

void AMyCharacter::MoveRight(float Axis)
{
	InputDirection.Y += Axis;
}

void AMyCharacter::MoveForward(float Axis)
{
	
	InputDirection.X += Axis;
}

void AMyCharacter::ZoomCamera(float Axis)
{
	if (!bSit &&CameraBoom->TargetArmLength + Axis * ZoomIncrement > 0 && CameraBoom->TargetArmLength + Axis * ZoomIncrement < ZoomMax)
		CameraBoom->TargetArmLength += Axis * ZoomIncrement;
}

void AMyCharacter::PauseGame()
{
	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->PauseGame();
}


bool AMyCharacter::IsSit()
{
	return bSit;
}
void AMyCharacter::InteractWithObject()
{
	FHitResult OutHit;

	FVector Start = Camera->GetComponentLocation();
	FVector ForwardVec = Camera->GetForwardVector();
	Start += (ForwardVec * CameraBoom->TargetArmLength);
	FVector End = Start + (ForwardVec * InteractRange);
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	if (FoodHeld)
		DropFood();
	else if (bSit)
	{
		StandUp();
	}
	else if (IsHit)
	{
		if (OutHit.GetActor()->GetClass()->IsChildOf(AFoodSpot::StaticClass()))
		{
			PickUpFoodFromSpot(Cast<AFoodSpot>(OutHit.GetActor()));
		}
		else if (OutHit.GetActor()->GetClass()->IsChildOf(AFood::StaticClass()) )
		{
			PickUpFood(Cast<AFood>(OutHit.GetActor()));
		}
		else if (OutHit.GetActor()->ActorHasTag("Chair"))
		{
			SitOnChair(OutHit.GetActor());
		}
	}
}
void AMyCharacter::SitOnChair(AActor* NewChair)
{
	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->SetCollisionProfileName(TEXT("OverlapAll"));
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);

	GetMesh()->AttachToComponent(Cast<AStaticMeshActor >(NewChair)->GetStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SitSocket"));
	GetCapsuleComponent()->AttachToComponent(Cast<AStaticMeshActor >(NewChair)->GetStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SitSocket"));
	bSit = true;
	CameraBoom->bUsePawnControlRotation = false;
	FRotator NewRotation = FRotator(0.0, 270.0, 0.0);
	CameraBoom->SetRelativeRotation(NewRotation, false);
	this->Chair = Cast<AStaticMeshActor >(NewChair)->GetStaticMeshComponent();
}
void AMyCharacter::StandUp()
{
	GetCapsuleComponent()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	GetMesh()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

	GetCapsuleComponent()->AttachToComponent(Chair, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeaveSocket"));
	GetMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeaveSocket"));

	GetMesh()->SetRelativeTransform(CharacterFeetPos);
	
	GetCapsuleComponent()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	bSit = false;
	CameraBoom->bUsePawnControlRotation = true;
	Chair = nullptr;
}