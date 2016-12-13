// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class STICKMAN_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//the mesh of the pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pickup)
	class UStaticMeshComponent* PickupMesh;

	//value of this pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 value;

	//Checks to see if the pickup is active or not
	UFUNCTION(BlueprintPure, Category=Pickup)
	bool IsActive();

	//sets the pickup to a specific value (active or inactive)
	UFUNCTION(BlueprintCallable, Category = Pickup)
	void SetActive(bool PickupState);

	//call this function when the pickup is collected
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	void WasCollected_Implementation();
protected:
	bool bIsActive;
};
