// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "Components/CapsuleComponent.h"
#include "../Player/MyPlayer.h"
#include "Component/StatComponent.h"


AMonster::AMonster()
{
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_capsuleComponent = GetCapsuleComponent();
    _capsuleComponent->OnComponentHit.AddDynamic(this, &AMonster::OnHit);

	bIsDead = false;
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
	AMyPlayer* player = Cast<AMyPlayer>(DamageCauser);



	if (bIsDead)
	{
		return 0.0f;
	}

	float damaged = -_StatCom->AddCurHp(-Damage);
	if (this->_StatCom->IsDead() && player != nullptr)
	{
		bIsDead = true;

		SetActorEnableCollision(false);
		auto controller = GetController();
		if (controller)
			GetController()->UnPossess();


		player->_StatCom->AddExp(GetExp());
		UE_LOG(LogTemp, Error, TEXT(" Add Exp : %d"), _exp);


	}
	return damaged;
}

void AMonster::LaunchFromPlayer(FVector LaunchDirection)
{
    FVector UpVector(0.0f, 0.0f, 200.f);
	LaunchCharacter((LaunchDirection * _launchLength) + UpVector, true, true);
}

void AMonster::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	AMyPlayer *Player = Cast<AMyPlayer>(OtherActor);
	if (Player && Player->IsDashing())
	{
		Player->OnMonsterHit(this, Hit);
	}
}


