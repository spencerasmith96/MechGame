// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleBullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Uobject/ConstructorHelpers.h"

// Sets default values
ASimpleBullet::ASimpleBullet()
{
 	//Use a box as simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	CollisionComp->BodyInstance.SetCollisionProfileName("ProjectileKinetic");

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set a dummy root component
	RootComponent = CollisionComp;

	//Mesh visible to player
	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleBulletMesh"));
	VisibleMesh->AttachToComponent(CollisionComp, FAttachmentTransformRules::KeepRelativeTransform);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// If found, uses bullet mesh by default
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("StaticMesh'/Game/CustomContent/Projectiles/BulletMesh.BulletMesh'"));
	if (BulletMeshAsset.Succeeded())
	{
		VisibleMesh->SetStaticMesh(BulletMeshAsset.Object);
		VisibleMesh->AddLocalRotation(FRotator(270.f, 0.f, 0.f));
		
		//Adjusts collision box to fit
		FVector BulletMinBound, BulletMaxBound;
		VisibleMesh->GetLocalBounds(BulletMinBound, BulletMaxBound);
		FVector NewBoxDimensions = BulletMaxBound.ComponentMax(BulletMinBound.GetAbs());
		NewBoxDimensions.Set(NewBoxDimensions.Z, NewBoxDimensions.Y, NewBoxDimensions.X);
		
		CollisionComp->SetBoxExtent(NewBoxDimensions);
	}

	// Die after 3 seconds by default
	//UPROPERTY(EditAnywhere)
	InitialLifeSpan = 4.f;
}

void ASimpleBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Hit!"));
}

// Called when the game starts or when spawned
void ASimpleBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

