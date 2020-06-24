// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleGun.generated.h"

UCLASS()
class MECHGAME_API ASimpleGun : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float FireRate;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* TurretMeshComp;

public:	
	// Sets default values for this actor's properties
	ASimpleGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:	
	// Called when the weapon is fired
	UFUNCTION(BlueprintCallable)
	void OnFire();

};
