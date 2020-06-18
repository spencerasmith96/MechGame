// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASimpleBullet::ASimpleBullet()
{
 	//Use a sphere as simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("ProjectileKinetic");

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	//Mesh visible to player
	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleBulletMesh"));
	VisibleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 500.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	//UPROPERTY(EditAnywhere)
	InitialLifeSpan = 3.0f;
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

