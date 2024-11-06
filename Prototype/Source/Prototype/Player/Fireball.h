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

    // Movement component for projectile movement
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovement;

    // Collision component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class USphereComponent* CollisionComponent;

    // Visual representation
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
    class UStaticMeshComponent* MeshComponent;

    // Damage value
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float _damage = 50.0f;

    // Function for handling collision
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

