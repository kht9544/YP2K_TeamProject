// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UENUM()
enum class ItemType
{
	Equipment,
	Consume,
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString _Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ItemType _Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString _Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* _Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* _Texture;
};

UCLASS()
class PROTOTYPE_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
