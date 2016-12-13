// Fill out your copyright notice in the Description page of Project Settings.

#include "StickMan.h"
#include "Pickup.h"
#include "StickManCharacter.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	/******************************************************************************/
	//initialize mesh and set it as the RootComponent of the object the mesh will be set inside a blueprint
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
	//all pickups start as active
	bIsActive = true;
	//default value of any pickup is 0
	value = 0;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//returns if a pickup is active or not
bool APickup::IsActive()
{
	return bIsActive;
}

//sets the value of active(if a pickup is alive or not)
void APickup::SetActive(bool PickupState)
{
	bIsActive = PickupState;
}

//implementation of WasCollected function
void APickup::WasCollected_Implementation()
{
	//get a reference to the player
	AStickManCharacter* stickMan = Cast<AStickManCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	//call addCoins based on the pickups value
	stickMan->addCoins(value);
	//Destroy the pickup
	Destroy();
}

