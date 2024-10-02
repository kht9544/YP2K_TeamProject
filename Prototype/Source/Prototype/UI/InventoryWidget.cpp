// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

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
}

void UInventoryWidget::ShowItem()
{
	if (_targetItem == nullptr)
	{
		ItemTexture->SetBrushFromTexture(_defaultTexture);
		ItemDesc->SetText(FText::FromString(_defaultText));
	}
}

void UInventoryWidget::ExchangeEquip(int32 slotIndex)
{
}
