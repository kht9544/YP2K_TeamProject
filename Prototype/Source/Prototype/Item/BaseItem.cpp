// Fill out your copyright notice in the Description page of Project Settings.



#include "Item/BaseItem.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

	//Setting Default Mesh and Texture
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> defaultMesh(
	// 	TEXT("/Script/Engine.StaticMesh'/Game/Kobo_Dungeon/Meshes/SM-Pottery-04.SM-Pottery-04'")
	// );
	// if (defaultMesh.Succeeded())
	// {
	// 	_meshComponent->SetStaticMesh(defaultMesh.Object);
	// }
	// static ConstructorHelpers::FObjectFinder<UTexture2D> defaultTexture(
	// 	TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_container_03_b.Tex_container_03_b'")
	// );
	// if (defaultTexture.Succeeded())
	// {
	// 	_Texture = defaultTexture.Object;
	// }

	_meshComponent->SetupAttachment(RootComponent);
	_trigger->SetupAttachment(_meshComponent);

	_trigger->SetSphereRadius(60.0f);

	_meshComponent->SetCollisionProfileName(TEXT("Item"));
	_trigger->SetCollisionProfileName(TEXT("Item"));
}

void ABaseItem::SetItemWithCode(int32 itemCode)
{

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

}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
