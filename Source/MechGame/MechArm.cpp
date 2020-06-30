// Fill out your copyright notice in the Description page of Project Settings.


#include "MechArm.h"
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
}

// Called when the game starts or when spawned
void AMechArm::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	
	if (World != NULL)
	{
		const FRotator SpawnRotation = WeaponLocation->GetComponentRotation();
		const FVector SpawnLocation = WeaponLocation->GetComponentLocation();

		if (WeaponComp != NULL)
		{
			ASimpleGun* NewWeapon = World->SpawnActor<ASimpleGun>(WeaponComp, SpawnLocation, SpawnRotation);
			NewWeapon->AttachToComponent(ArmSkeletalComp, FAttachmentTransformRules::KeepWorldTransform, TEXT("Weapon1"));

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

}

