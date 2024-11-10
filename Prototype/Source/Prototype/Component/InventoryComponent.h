// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseItem;
class UInventoryWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(int32 slot = 0, ABaseItem* item = nullptr);
	virtual void InitializeComponent() override;

	TArray<ABaseItem*> GetItemSlots(){return _ItemSlots;}
	TArray<int32> GetEmptySlots(){return _EmptySlots;}
	TMap<FString, class AEquipItem*> GetEquipSlots(){return _EquipSlots;}

	void SetItemSlots(TArray<ABaseItem*> item ){_ItemSlots = item;}
	void SetEmptySlots(TArray<int32> empty ){_EmptySlots = empty;}
	void SetEquipSlots(TMap<FString, class AEquipItem*> equip){_EquipSlots = equip;}
	
	UFUNCTION()
	void ExcuteItem(int32 slot, bool isDrop);
	void EquipItem(int32 slot);
	void TryEquip(FString part, int32 slot);

private:
	void UIupdate_Add(int32 slot, ABaseItem* item);
	void UIupdate_Pop(int32 slot);
	void UIupdate_equip(int32 slot, ABaseItem* item);
	//Trigger
	bool _isSlotFull = false;
	int32 _itemSlotMax = 12;
	int32 _equipSlotMax = 6;

	void SlotFullCheck();

	//Property
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TArray<ABaseItem*> _ItemSlots;

	TArray<int32> _EmptySlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TMap<FString, class AEquipItem*> _EquipSlots;
};
