// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "AICharacter.h"
#include "MyGC_UE4CPPGameModeBase.h"

void AMyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->ActorHasTag("Food") )
	{
		
		//PickUpFood(Cast<AFood>(OtherActor));
		
		//OtherActor->K2_AttachToActor(this, OtherActor->GetAttachParentSocketName(), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	}
	else if(OtherActor->ActorHasTag("FoodSlot"))
	{

		
		AFoodSpot* spot = Cast<AFoodSpot>(OtherActor);
		PutFoodOnSpot(spot);
		//DropFood();
	}
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
	
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::PauseGame);

	PlayerInputComponent->BindAction("FoodAction", IE_Pressed,this, &AMyCharacter::FoodAction);
}

void AMyCharacter::MoveRight(float axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	float modifier = (FoodHeld != nullptr) ? 0.5f : 1.0f;
	AddMovementInput(Direction* modifier, axis);
}

void AMyCharacter::MoveForward(float axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	float modifier = (FoodHeld != nullptr) ? 0.5f : 1.0f;
	AddMovementInput(Direction * modifier, axis);
}

void AMyCharacter::ZoomCamera(float axis)
{
	if (CameraBoom->TargetArmLength + axis * ZOOM_INCREMENT > 0 && CameraBoom->TargetArmLength + axis * ZOOM_INCREMENT < ZOOM_MAX)
		CameraBoom->TargetArmLength += axis * ZOOM_INCREMENT;
}

void AMyCharacter::PauseGame()
{
	AMyGC_UE4CPPGameModeBase* GameMode = Cast<AMyGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->PauseGame();
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
	FVector End = Start + (ForwardVec * 200.0f);
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

		//
		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
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
	}
	if (!bHavepick && FoodHeld)
		DropFood();

}

