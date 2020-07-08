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

	// Readies the arm for firing
	void ReadyFire();

	// Changes active weapon
	void CycleWeapon();

private:
	// Adds weapon to the appropriate socket
	void AddWeapon(TSubclassOf<ASimpleGun> NewGun, FName SocketName);

private: 
	ASimpleGun* ActiveWeapon;

	TArray<ASimpleGun*> WeaponList;
};
