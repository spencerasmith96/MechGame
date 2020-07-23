// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SimpleGun.h"
#include "MechArm.generated.h"

UCLASS()
class MECHGAME_API AMechArm : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* ArmSkeletalComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASimpleGun> WeaponComp1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASimpleGun> WeaponComp2;

	UPROPERTY(EditAnywhere)
	UAnimBlueprint* ArmPoseAsset;

	/** Over shoulder camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* OverShoulderCameraComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* WeaponLocation;

	UPROPERTY(EditAnywhere)
	UAnimationAsset* ReadyFireAnim;

public:
	// Sets default values for this pawn's properties
	AMechArm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Tries to fire ActiveWeapon
	void OnFire();

	// Turn active weapon Right/Left
	void TurnRight(float Val);

	// Turn arm Up/Down
	void LookUp(float Val);

	// Changes to next active weapon
	void CycleWeapon();

	// Changes to the weapon at the index, false if failed
	bool CycleToWeapon(int32 index);

	// Returns the active weapon as index
	UFUNCTION(BlueprintCallable, Category = "MechArm")
	int32 GetActiveWeaponSlot();

private:
	// Adds weapon to the appropriate socket
	void AddWeapon(TSubclassOf<ASimpleGun> NewGun, FName SocketName);

private: 
	ASimpleGun* ActiveWeapon;

	int32 ActiveWeaponSlot = 0;

	TArray<ASimpleGun*> WeaponList;
};
