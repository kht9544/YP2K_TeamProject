// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseItem.h" 
#include "EquipItem.generated.h"

UCLASS()
class PROTOTYPE_API AEquipItem : public ABaseItem 
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AEquipItem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
  
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    //TODO: 스켈레톤으로 변경예정
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    // UStaticMeshComponent* _itemMesh;

    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    // class USphereComponent* _overlapSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class USkeletalMeshComponent* _skeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
    FName AttachSocketName;

public:  
    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
