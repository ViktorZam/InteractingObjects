// Copyright Epic Games, Inc. All Rights Reserved.

#include "interacting_objectsCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"


//////////////////////////////////////////////////////////////////////////
// Ainteracting_objectsCharacter

Ainteracting_objectsCharacter::Ainteracting_objectsCharacter()
{


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	CharacteristicsComponent = CreateDefaultSubobject<UCharacteristics>(TEXT("Characteristics"));
	bReplicates = true;
	//InputComponent->SetIsReplicated(true);
	//AActor::bReplicateMovement = true;
	//bReplicates = true;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void Ainteracting_objectsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &Ainteracting_objectsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &Ainteracting_objectsCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &Ainteracting_objectsCharacter::TurnCamera);
	PlayerInputComponent->BindAxis("TurnRate", this, &Ainteracting_objectsCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &Ainteracting_objectsCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &Ainteracting_objectsCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &Ainteracting_objectsCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &Ainteracting_objectsCharacter::OnResetVR);
}


void Ainteracting_objectsCharacter::OnResetVR()
{
	// If interacting_objects is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in interacting_objects.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void Ainteracting_objectsCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void Ainteracting_objectsCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void Ainteracting_objectsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void Ainteracting_objectsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void Ainteracting_objectsCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		Speed_W_S = Value;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%f"), Rotation.Yaw));
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		
		//Speed_W_S = 0;
	}
}

void Ainteracting_objectsCharacter::MoveRight(float Value)
{
	test = Value + 1;
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		Speed_A_D = Value;
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		//Speed_A_D = 0;
	}
}

void Ainteracting_objectsCharacter::TurnCamera(float Value)
{
	SpeedTurnCamera = Value;
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%f"), SpeedTurnCamera));
	
	if (Value != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddYawInput(Value);
		
		if (SpeedTurnCamera != 0) {
			SpeedTurnCamera = SpeedTurnCamera * 2.5;
			FRotator CurrentActorRotation = this->GetActorRotation();
			SpeedTurnCamera = CurrentActorRotation.Yaw + SpeedTurnCamera;
			FRotator NewRotation = FRotator(0, SpeedTurnCamera, 0);
			this->SetActorRotation(NewRotation, ETeleportType::None);

		}
		
		
	}
}

void Ainteracting_objectsCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(Ainteracting_objectsCharacter, Speed_A_D);
	DOREPLIFETIME(Ainteracting_objectsCharacter, Speed_W_S);
	DOREPLIFETIME(Ainteracting_objectsCharacter, test);
	//UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	//if (BPClass) BPClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
}


void Ainteracting_objectsCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	//test = test + 0.00001;
	
}

