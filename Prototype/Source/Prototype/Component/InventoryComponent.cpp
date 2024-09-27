// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SlotFullCheck()
{
	for (int i = 0; i < _itemSlotMax; i++)
	{
		if (_ItemSlots[i] == nullptr)
		{
			_isSlotFull = false;
			return;
		}
	}
	_isSlotFull = true;
}

void UInventoryComponent::AddItem(int32 slot, ABaseItem* item)
{
	if (item == nullptr)
		return;
	if (slot >= _itemSlotMax)
		return;
	if (_isSlotFull)
		return;
	//TODO : Fill into EmptySlot First
	if (!_EmptySlots.IsEmpty())
	{
		int32 emptyslot;
		_EmptySlots.HeapPop(emptyslot, true);
		SlotFullCheck();
		UIupdate_Add(emptyslot, item);
		return;
	}
	//Fill into Selected Slot
	if (_ItemSlots[slot] == nullptr)
	{
		_ItemSlots[slot] = item;
		UIupdate_Add(slot, item);
		SlotFullCheck();
	}
	//if Already filled, fill into next slot
	else
	{
		for (int i = slot; i < _itemSlotMax; i++)
		{
			if (_ItemSlots[i] != nullptr)
				continue;
			_ItemSlots[i] = item;
			UIupdate_Add(i, item);
			SlotFullCheck();
			return;
		}
		return;
	}
}

void UInventoryComponent::ExcuteItem(int32 slot, bool isDrop)
{
}

void UInventoryComponent::EquipItem(int32 slot)
{
}

void UInventoryComponent::SelectItem(int32 slot)
{
}

void UInventoryComponent::UIupdate_Add(int32 slot, ABaseItem* item)
{
}

void UInventoryComponent::UIupdate_Pop(int32 slot)
{
}

void UInventoryComponent::UIupdate_equip(int32 slot, ABaseItem* item)
{
}
