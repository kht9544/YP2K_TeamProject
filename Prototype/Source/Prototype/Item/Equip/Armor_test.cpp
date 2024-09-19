// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor_test.h"
#include "../../Player/MyPlayer.h"
#include "Components/SphereComponent.h"

// Sets default values
AArmor_test::AArmor_test()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = false;

	_armor = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ARMOR"));
	RootComponent = _armor;

	_overlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	_overlapSphere->SetupAttachment(_armor);
	_overlapSphere->SetSphereRadius(100.0f); 
	_overlapSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AM
	(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_01/mesh/armor/SK_SKnight_01_Torso.SK_SKnight_01_Torso'"));

	if (AM.Succeeded())
		_armor->SetSkeletalMesh(AM.Object);

	_armor->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AArmor_test::BeginPlay()
{
	Super::BeginPlay();
	_overlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AArmor_test::OnCharacterOverlap);

	
}

void AArmor_test::OnCharacterOverlap(UPrimitiveComponent* OVerlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto PlayerCharacter = Cast<AMyPlayer>(OtherActor);
	if (PlayerCharacter != nullptr)
	{
		if (PlayerCharacter->CanSetArmor())
		{
			PlayerCharacter->SetArmor(this);
			SetActorEnableCollision(false);
		}
	}
}

// Called every frame
void AArmor_test::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

