// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Equip/EquipItem.h"
#include "../../Player/MyPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AEquipItem::AEquipItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	_itemMesh->SetSimulatePhysics(true);
	RootComponent = _itemMesh;

	_overlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	_overlapSphere->SetupAttachment(_itemMesh);
	_overlapSphere->SetSphereRadius(100.0f);
	_overlapSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	AttachSocketName = FName(TEXT(""));
}

// Called when the game starts or when spawned
void AEquipItem::BeginPlay()
{
	Super::BeginPlay();

	_overlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AEquipItem::OnOverlapBegin);
}

// Called every frame
void AEquipItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEquipItem::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	AMyPlayer *Player = Cast<AMyPlayer>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapplayer"));
		AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocketName);

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}
