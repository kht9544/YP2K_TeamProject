// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"


AMonster::AMonster()
{
    
}

void AMonster::BeginPlay()
{
    Super::BeginPlay();
}

void AMonster::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AMonster::Disable()
{
    Super::Disable();
}

void AMonster::DropReword()
{
    
}

float AMonster::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return 0.0f;
}

