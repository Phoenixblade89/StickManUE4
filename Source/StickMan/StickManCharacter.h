// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "StickManCharacter.generated.h"

UCLASS(config=Game)
class AStickManCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CollectionSphere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;
protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	//Called when we press a key to collect pickups inside the collection sphere
	UFUNCTION(BlueprintCallable, Category = Pickups)
	void CollectPickups();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


public:
	AStickManCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Coins)
	int32 coins;

	UFUNCTION(BlueprintCallable, Category = Pickups)
	void addCoins(int32 coin_value);
	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }
};
