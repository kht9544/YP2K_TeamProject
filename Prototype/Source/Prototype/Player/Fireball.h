// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fireball.generated.h"

UCLASS()
class PROTOTYPE_API AFireball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;



private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",meta=(AllowPrivateAccess = true))
    class UProjectileMovementComponent* _moveCom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision",meta=(AllowPrivateAccess = true))
    class USphereComponent*  _sphereCom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual",meta=(AllowPrivateAccess = true))
    class UStaticMeshComponent* _meshCom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",meta=(AllowPrivateAccess = true))
    float _damage = 50.0f;

    	UFUNCTION()
	void OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);
};

