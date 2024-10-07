// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "../Player/MyPlayer.h"


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

void AMonster::LaunchFromPlayer(FVector LaunchDirection)
{
    FVector UpVector(0.0f, 0.0f, 200.f);
	LaunchCharacter((LaunchDirection * _launchLength) + UpVector, true, true);
    UE_LOG(LogTemp,Warning,TEXT("Launh"));
}

void AMonster::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	AMyPlayer *Player = Cast<AMyPlayer>(OtherActor);
	if (Player && Player->IsDashing())
	{
		Player->OnMonsterHit(this, Hit);
	}
}
