// Fill out your copyright notice in the Description page of Project Settings.


#include "MechArm.h"
#include "Camera/CameraComponent.h"
#include "SimpleGun.h"

// Sets default values
AMechArm::AMechArm()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArmSkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmSkeletealComponent"));
	RootComponent = ArmSkeletalComp;

	WeaponLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponLocation"));
	WeaponLocation->AttachToComponent(ArmSkeletalComp, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon1"));

	OverShoulderCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	OverShoulderCameraComponent->SetupAttachment(ArmSkeletalComp);
	FVector CamLocation = FVector(-2400.f, 1800.f, -700.f);
	OverShoulderCameraComponent->SetRelativeLocation(CamLocation);
}

// Called when the game starts or when spawned
void AMechArm::BeginPlay()
{
	Super::BeginPlay();

	// Spawns the WeaponComp at the location of WeaponLocation and attaches to the socket
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		const FRotator SpawnRotation = WeaponLocation->GetComponentRotation();
		const FVector SpawnLocation = WeaponLocation->GetComponentLocation();

		if (WeaponComp != NULL)
		{
			ASimpleGun* NewWeapon = World->SpawnActor<ASimpleGun>(WeaponComp, SpawnLocation, SpawnRotation);
			NewWeapon->AttachToComponent(ArmSkeletalComp, FAttachmentTransformRules::KeepWorldTransform, TEXT("Weapon1"));

			// Temporary!!!
			// Sets ActiveWeapon to NewWeapon
			ActiveWeapon = NewWeapon;
		}
	}
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
}

void AMechArm::OnFire()
{
	if (ActiveWeapon != NULL)
	{
		ActiveWeapon->OnFire();
	}
}

