// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Creature.h"

// Sets default values
ACreature::ACreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACreature::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACreature::Init()
{
	
}

void ACreature::Disable()
{
	
}

float ACreature::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}



