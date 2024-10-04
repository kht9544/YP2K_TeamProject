// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

#include "Item/BaseItem.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

bool UInventoryWidget::Initialize()
{
	bool result = Super::Initialize();



	return result;
}

void UInventoryWidget::SetButtons()
{
	
}

void UInventoryWidget::SetItemImage(int32 slotIndex, ABaseItem* item)
{
	if (item == nullptr)
	{
		Image_[slotIndex]->SetBrushFromTexture(_defaultTexture);
	}
	Image_[slotIndex]->SetBrushFromTexture(item->GetTexture());
}

void UInventoryWidget::ShowItem()
{
	if (_targetItem == nullptr)
	{
		ItemTexture->SetBrushFromTexture(_defaultTexture);
		ItemDesc->SetText(FText::FromString(_defaultText));
	}
	else
	{
		ItemTexture->SetBrushFromTexture(_targetItem->GetTexture());
		ItemDesc->SetText(FText::FromString(_targetItem->GetDesc()));
	}
}

void UInventoryWidget::ExchangeEquip(int32 slotIndex)
{
}

void UInventoryWidget::DropItem()
{
	if (_targetItem == nullptr)
		return;

	ItemDrop.Broadcast(_targetIndex, true);

	_targetItem = nullptr;
	ShowItem();
	SetItemImage(_targetIndex, nullptr);
	_targetIndex = -1;
}

void UInventoryWidget::UseItem()
{
	if (_targetItem == nullptr)
		return;

	ItemDrop.Broadcast(_targetIndex, false);

	_targetItem = nullptr;
	ShowItem();
	SetItemImage(_targetIndex, nullptr);
	_targetIndex = -1;
}
