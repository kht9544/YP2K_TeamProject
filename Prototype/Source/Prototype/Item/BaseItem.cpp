// Fill out your copyright notice in the Description page of Project Settings.



#include "Item/BaseItem.h"

#include "Player/MyPlayer.h"

#include "Base/MyGameInstance.h"
#include "Component/InventoryComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

	_meshComponent->SetupAttachment(RootComponent);
	_trigger->SetupAttachment(_meshComponent);

	_trigger->SetSphereRadius(60.0f);

	_meshComponent->SetCollisionProfileName(TEXT("Item"));
	_trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ABaseItem::SetItemWithCode(int32 itemCode)
{
	auto gameinstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (gameinstance != nullptr)
	{
		FItemData* data = gameinstance->GetConsumeItemData(itemCode);
		if (data == nullptr || data->_Name == TEXT(""))
		{
			UE_LOG(LogTemp, Error, TEXT("Data Load Faild!"));
			return;
		}

		_Texture = data->_Texture;
		_Mesh = data->_Mesh;
		_Value = data->_Value;
		_Price = data->_Price;
		_Name = data->_Name;
		_Type = data->_Type;
		_ModStatType = data->_ModTarget;
		_Description = data->_Description;

		_meshComponent->SetStaticMesh(_Mesh);
	}
}

void ABaseItem::Init()
{
	_meshComponent->SetStaticMesh(_Mesh);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseItem::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
 void ABaseItem::BeginPlay()
 {
	Super::BeginPlay();
 }

 void ABaseItem::PostInitializeComponents()
 {
	 Super::PostInitializeComponents();

	 _trigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapBegin);
 }

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ABaseItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_player = Cast<AMyPlayer>(OtherActor);
	if (_player == nullptr)
		return;
	UE_LOG(LogTemp, Warning, TEXT("Player Collision!"));
	_player->GetItem(this);
	Disable();
}

void ABaseItem::GetItem()
{

}

void ABaseItem::UseItem()
{
}

void ABaseItem::DropItem(FVector location, FRotator rotation)
{
	SetActorLocationAndRotation(location, rotation);
	Init();
}
