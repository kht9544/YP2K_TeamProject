// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonster.h"
#include "../Player/MyPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANormalMonster::ANormalMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PS(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton/mesh/SK_Skeleton_base.SK_Skeleton_base'"));

	if (PS.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PS.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_capsuleComponent = GetCapsuleComponent();
    
    _capsuleComponent->OnComponentHit.AddDynamic(this, &ANormalMonster::OnHit);

    _launchLength = 1000.0f;

}

// Called when the game starts or when spawned
void ANormalMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANormalMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANormalMonster::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
 //   if (Player && Player->IsDashing())
 //   {
 //       Player->OnMonsterHit(this, Hit);
 //   }
}

void ANormalMonster::LaunchFromPlayer(FVector LaunchDirection, float LaunchStrength)
{
	FVector UpVector(0.0f,0.0f,100.f);
	LaunchCharacter((LaunchDirection * LaunchStrength) + UpVector, true, true);
}

