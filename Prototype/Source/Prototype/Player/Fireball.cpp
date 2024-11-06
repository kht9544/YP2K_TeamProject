// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Fireball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MyPlayer.h"
#include "../Monster/Monster.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFireball::AFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sphereCom = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    _sphereCom->InitSphereRadius(15.0f);
    _sphereCom->SetCollisionProfileName(TEXT("Projectile"));
    _sphereCom->SetMobility(EComponentMobility::Movable);
    RootComponent = _sphereCom;

    _meshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    _meshCom->SetupAttachment(RootComponent);
    _meshCom->SetMobility(EComponentMobility::Movable);

    _moveCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    _moveCom->UpdatedComponent = _sphereCom;
    _moveCom->InitialSpeed = 3000.0f;
    _moveCom->MaxSpeed = 3000.0f;
    _moveCom->bRotationFollowsVelocity = true;
    _moveCom->bShouldBounce = true;
    _moveCom->ProjectileGravityScale = 0.0f;

    InitialLifeSpan = 3.0f;
   

}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();
	
     _sphereCom->OnComponentBeginOverlap.AddDynamic(this, &AFireball::OnMyCharacterOverlap);
}

// Called every frame
void AFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireball::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
    auto monster = Cast<AMonster>(OtherActor);

	_damage = 70;

	if (monster != nullptr)
	{
        
        Destroy();
	}
}



