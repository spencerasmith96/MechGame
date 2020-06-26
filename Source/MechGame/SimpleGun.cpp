// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGun.h"
#include "SimpleBullet.h"
#include "Components/AudioComponent.h"

// Sets default values
ASimpleGun::ASimpleGun()
{
	// Creates the turret skele mesh component
	TurretMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	RootComponent = TurretMeshComp;

	// Creates a component that'll snap to TurretMesh's "Muzzle" socket
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(TurretMeshComp, TEXT("Muzzle"));

	// Initiliazes the audio firing of the gun
	FireAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("FireAudioComponent"));
	FireAudioComp->bAutoActivate = false;
	FireAudioComp->AttachToComponent(MuzzleLocation, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASimpleGun::BeginPlay()
{
	Super::BeginPlay();
	FireAudioComp->SetSound(FireSound);
	OnFire();
}

void ASimpleGun::OnFire()
{
	// Try to play the fire animation
	if (FireAnimation != NULL)
	{
		TurretMeshComp->PlayAnimation(FireAnimation, false);
	}

	// Try to spawn the bullet
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
	// Try to play sound effect
	if (FireSound != NULL)
	{
		FireAudioComp->Play();
	}
}

