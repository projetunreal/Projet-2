// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "AICharacter.h"
#include "MyGC_UE4CPPGameModeBase.h"



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
	TriggerCapsule = GetCapsuleComponent();
	TriggerCapsule = GetCapsuleComponent();
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraBoom->TargetArmLength = 300.0f;

	CameraBoom->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyCharacter::MoveCameraRight);
	PlayerInputComponent->BindAxis("Vertical", this, &AMyCharacter::MoveCameraDown);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Zoom", this, &AMyCharacter::ZoomCamera);
	
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::PauseGame);

	PlayerInputComponent->BindAction("FoodAction", IE_Pressed,this, &AMyCharacter::FoodAction);
}

void AMyCharacter::MoveRight(float axis)
{
	if (!bSit)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		float modifier = (FoodHeld != nullptr) ? 0.5f : 1.0f;
		AddMovementInput(Direction * modifier, axis);
	}
}

void AMyCharacter::MoveForward(float axis)
{
	if (!bSit)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		float modifier = (FoodHeld != nullptr) ? 0.5f : 1.0f;
		AddMovementInput(Direction * modifier, axis);

	}
}

void AMyCharacter::ZoomCamera(float axis)
{
	if (!bSit &&CameraBoom->TargetArmLength + axis * ZOOM_INCREMENT > 0 && CameraBoom->TargetArmLength + axis * ZOOM_INCREMENT < ZOOM_MAX)
		CameraBoom->TargetArmLength += axis * ZOOM_INCREMENT;
}

void AMyCharacter::PauseGame()
{
	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->PauseGame();
}

void AMyCharacter::MoveCameraRight(float axis)
{
	if (!bSit)
		AddControllerYawInput(axis);
}
void AMyCharacter::MoveCameraDown(float axis)
{
	if (!bSit)
		AddControllerPitchInput(axis);
}
bool AMyCharacter::IsSit()
{
	return bSit;
}
void AMyCharacter::FoodAction()
{

	//if (FoodHeld)
	//{

	//	DropFood();
	//}
	bool bHavepick = false ;
	FHitResult OutHit;

	FVector Start = Camera->GetComponentLocation();
	FVector ForwardVec = Camera->GetForwardVector();

	Start += (ForwardVec * CameraBoom->TargetArmLength);
	FVector End = Start + (ForwardVec * 300.0);
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

		//
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	if (IsHit)
	{
		if (OutHit.GetActor()->GetClass()->IsChildOf(AFoodSpot::StaticClass()))
		{
			bHavepick = true;
			PickUpFoodFromSpot(Cast<AFoodSpot>(OutHit.GetActor()));
		}
		else if (OutHit.GetActor()->GetClass()->IsChildOf(AFood::StaticClass()) && !FoodHeld)
		{
			bHavepick = true;
			PickUpFood(Cast<AFood>(OutHit.GetActor()));
		}
		else if (OutHit.GetActor()->ActorHasTag("Chair"))
		{
			UE_LOG(LogTemp, Warning, TEXT("test"));
			GetMesh()->SetSimulatePhysics(false);
			GetMesh()->SetCollisionProfileName(TEXT("OverlapAll"));
			FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
			GetMesh()->AttachToComponent(Cast<AStaticMeshActor >(OutHit.GetActor())->GetStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SitSocket"));
			bSit = true;
			CameraBoom->bUsePawnControlRotation = false;
			// NewRotation=FRotator(0.0,0.0,180);
			//FVector NewLocation = FVector(0.0, 0.0, 0);
			//CameraBoom->SetWorldRotation(NewRotation,false);
		}
	}
	if (!bHavepick && FoodHeld)
		DropFood();

}
/*
void AMyCharacter::PlusReleased()
{
	AInGameHUD* HUD = Cast<AInGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	HUD->UpdateFoodCount(1);
}
*/