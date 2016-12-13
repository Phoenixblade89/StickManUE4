// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "StickMan.h"
#include "StickManCharacter.h"
#include "Pickup.h"

AStickManCharacter::AStickManCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	/********************************************My Additions****************************************************/
	//set default coin value for StickMan
	coins = 0;

	//create a sphere around the player for use with collision detection
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	//connect the sphere to the rootcomponent
	CollectionSphere->SetupAttachment(RootComponent);
	//setup how large the sphere is by default
	CollectionSphere->SetSphereRadius(100.f);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStickManCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStickManCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AStickManCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AStickManCharacter::TouchStopped);

	/*************************************************************************************/
	PlayerInputComponent->BindAction("Collect", IE_Pressed, this, &AStickManCharacter::CollectPickups);
}

void AStickManCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AStickManCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AStickManCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

//function to add the value of a coin to the players collection
void AStickManCharacter::addCoins(int32 coin_value)
{
	coins += coin_value;
}

void AStickManCharacter::CollectPickups()
{
	//get all overlapping actors and store them
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);
	//loop through each actor
	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		//cast to APickup
		APickup* const testPickup = Cast<APickup>(CollectedActors[i]);
		//if cast works and pickup is valid and active
		if (testPickup && !testPickup->IsPendingKill() && testPickup->IsActive())
		{
			//call the pickups WasCollected function and add it's value to the coin count
			testPickup->WasCollected();
			//deactive the pickup
			testPickup->SetActive(false);
		}
	}
}
// Called every frame
void AStickManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//call CollectPickups each frame so the user can just run into coins to collect them
	CollectPickups();
}