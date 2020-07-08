// Fill out your copyright notice in the Description page of Project Settings.


#include "MechArm.h"
#include "Camera/CameraComponent.h"
#include "SimpleGun.h"

// Sets default values
AMechArm::AMechArm()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup skeletal mesh for the arm
	ArmSkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmSkeletealComponent"));
	RootComponent = ArmSkeletalComp;

	// Setup scene component for weapon location
	WeaponLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponLocation"));
	WeaponLocation->AttachToComponent(ArmSkeletalComp, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon1"));

	// Setup CameraComponent
	OverShoulderCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	OverShoulderCameraComponent->SetupAttachment(ArmSkeletalComp);
	FVector CamLocation = FVector(-2400.f, 1800.f, -700.f);
	OverShoulderCameraComponent->SetRelativeLocation(CamLocation);
}

// Called when the game starts or when spawned
void AMechArm::BeginPlay()
{
	Super::BeginPlay();

	// Spawns the WeaponComps at the location of WeaponLocation and attaches to the socket
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		const FRotator SpawnRotation = WeaponLocation->GetComponentRotation();
		const FVector SpawnLocation = WeaponLocation->GetComponentLocation();

		if (WeaponComp1 != NULL)
		{
			ASimpleGun* NewWeapon = World->SpawnActor<ASimpleGun>(WeaponComp1, SpawnLocation, SpawnRotation);
			NewWeapon->AttachToComponent(ArmSkeletalComp, FAttachmentTransformRules::KeepWorldTransform, TEXT("Weapon1"));

			// Temporary!!!
			// Sets ActiveWeapon to NewWeapon
			ActiveWeapon = NewWeapon;
		}

		if (WeaponComp2 != NULL)
		{
			ASimpleGun* NewWeapon = World->SpawnActor<ASimpleGun>(WeaponComp2, SpawnLocation, SpawnRotation);
		}
	}

	ReadyFire();

}

// Called every frame
void AMechArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMechArm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMechArm::OnFire);

	// Bind rotation
	PlayerInputComponent->BindAxis("Turn", this, &AMechArm::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMechArm::LookUp);
}

void AMechArm::OnFire()
{
	if (ActiveWeapon != NULL)
	{
		ActiveWeapon->OnFire();
	}
}

void AMechArm::TurnRight(float Val)
{
	FRotator RotateOffset = FRotator(0.f, Val, 0.f);
	ActiveWeapon->GetRootComponent()->AddLocalRotation(RotateOffset);
}

void AMechArm::LookUp(float Val)
{
	FRotator RotateOffset = FRotator(Val, 0.f, 0.f);
	ArmSkeletalComp->AddLocalRotation(RotateOffset);
}

void AMechArm::ReadyFire()
{
	if (ReadyFireAnim != NULL)
	{
		ArmSkeletalComp->PlayAnimation(ReadyFireAnim, false);
	}
	if (ActiveWeapon != NULL)
	{
		OverShoulderCameraComponent->AttachToComponent(ActiveWeapon->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	}
}

