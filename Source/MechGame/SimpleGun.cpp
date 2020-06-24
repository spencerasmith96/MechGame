// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGun.h"
#include "SimpleBullet.h"

// Sets default values
ASimpleGun::ASimpleGun()
{
	// Creates the turret skele mesh component
	TurretMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	RootComponent = TurretMeshComp;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(TurretMeshComp, TEXT("Muzzle"));
	
}

// Called when the game starts or when spawned
void ASimpleGun::BeginPlay()
{
	Super::BeginPlay();
	OnFire();
}

void ASimpleGun::OnFire()
{
	if (FireAnimation != NULL)
	{
		UAnimInstance* AnimInstance = TurretMeshComp->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to find AnimInstance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find FireAnimation"));
	}
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
			const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();
			World->SpawnActor<ASimpleBullet>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}
}

