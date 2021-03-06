// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleBullet.generated.h"

UCLASS()
class MECHGAME_API ASimpleBullet : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileKinetic")
	class UBoxComponent* CollisionComp;

	/** Visible mesh of bullet */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisibleMesh;

	/** Projectile movement component */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Movement, meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* ProjectileMovement;

private:
	/** Value of projectile's damage */
	UPROPERTY(EditAnywhere)
	int32 Damage = 1;

public:	
	// Sets default values for this actor's properties
	ASimpleBullet();

	/** Called when bullet hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }

	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
