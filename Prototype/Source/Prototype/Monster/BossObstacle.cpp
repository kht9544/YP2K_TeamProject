// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BossObstacle.h"
#include "BossMonster.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABossObstacle::ABossObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName("BlockAll");
	CollisionBox->OnComponentHit.AddDynamic(this,&ABossObstacle::OnHit);
	RootComponent = CollisionBox;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABossObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossObstacle::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(ABossMonster* Boss = Cast<ABossMonster>(OtherActor))
	{
		Destroy();
	}
}

