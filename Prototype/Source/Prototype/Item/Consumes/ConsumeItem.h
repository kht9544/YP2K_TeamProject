// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ConsumeItem.generated.h"

UENUM()
enum class ItemSpecipic
{
	HP_Postion,
	MP_Postion,
	EXP_orb,
};

UCLASS()
class PROTOTYPE_API AConsumeItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AConsumeItem();

	ItemSpecipic GetSpecipic() { return _specipic; }

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	ItemSpecipic _specipic;
};
