// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGun.h"

// Sets default values
ASimpleGun::ASimpleGun()
{
	TurretMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Turret Mesh"));
}

// Called when the game starts or when spawned
void ASimpleGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASimpleGun::OnFire()
{
}

