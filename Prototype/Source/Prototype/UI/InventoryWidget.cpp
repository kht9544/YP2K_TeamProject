// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "Components/UniformGridPanel.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "UI/Elements/IndexedButton.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

#include "Item/BaseItem.h"
#include "Item/Equip/EquipItem.h"
#include "Item/Consumes/ConsumeItem.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

bool UInventoryWidget::Initialize()
{
	bool result = Super::Initialize();

	SetItemButtons();

	Button_[0]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem0);
	Button_[1]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem1);
	Button_[2]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem2);
	Button_[3]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem3);
	Button_[4]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem4);
	Button_[5]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem5);
	Button_[6]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem6);
	Button_[7]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem7);
	Button_[8]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem8);
	Button_[9]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem9);
	Button_[10]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem10);
	Button_[11]->OnClicked.AddDynamic(this, &UInventoryWidget::TargetItem11);

	DropBtn->OnClicked.AddDynamic(this, &UInventoryWidget::DropItem);
	UseBtn->OnClicked.AddDynamic(this, &UInventoryWidget::UseItem);

	return result;
}

void UInventoryWidget::SetItemButtons()
{
	TArray<UWidget*> widgets;
	widgets = ItemSlots->GetAllChildren();

	int32 index = 0;
	for (UWidget* widget : widgets)
	{
		UIndexedButton* button = Cast<UIndexedButton>(widget);
		if (button)
		{
			button->SetIndex(index);
			button->SetIsEnabled(true);
			//button->OnClicked.AddDynamic(this, UMyInventoryUI::ShowItem);
			Button_.Add(button);

			index++;
		}
	}
}

void UInventoryWidget::SetEquipButtons()
{
	
}

void UInventoryWidget::SetStats()
{
}

void UInventoryWidget::SetItemImage(int32 slotIndex, ABaseItem* item)
{
	if (item == nullptr)
	{
		Button_[slotIndex]->SetItem(nullptr);
		Button_[slotIndex]->SetImage(T_DEFAULT);
		Button_[slotIndex]->ButtonUpdate();
	}
	else
	{
		Button_[slotIndex]->SetItem(item);
		UTexture2D* texture = item->GetTexture();
		if (texture == nullptr) texture = T_DEFAULT;
	
		Button_[slotIndex]->SetImage(texture);
		Button_[slotIndex]->ButtonUpdate();
	}
}

void UInventoryWidget::SetEquipImage(int32 slotIndex, ABaseItem* item)
{
	//TODO : Setting Equip Item Buttons Image
}

void UInventoryWidget::ShowItem()
{
	if (_targetItem == nullptr)
	{
		ItemTexture->SetBrushFromTexture(T_DEFAULT);
		ItemName->SetText(FText::FromString(_defaultText));
		ItemDesc->SetText(FText::FromString(_defaultText));
	}
	else
	{
		if (Cast<AEquipItem>(_targetItem))
		{
			UseBtnText->SetText(FText::FromString(TEXT("Equip")));
		}
		else
		{
			UseBtnText->SetText(FText::FromString(TEXT("Use")));
		}
		ItemTexture->SetBrushFromTexture(_targetItem->GetTexture());
		ItemName->SetText(FText::FromString(_targetItem->GetName()));
		ItemDesc->SetText(FText::FromString(_targetItem->GetDesc()));
	}
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

	if (Cast<AEquipItem>(_targetItem))
	{
		CheckCanEquip();

		ItemEquip.Broadcast(_targetIndex);
	}
	if (Cast<AConsumeItem>(_targetItem))
	{
		ItemDrop.Broadcast(_targetIndex, false);
		ItemUse.Broadcast(_targetIndex);
		_targetItem = nullptr;
	}
	ShowItem();
	SetItemImage(_targetIndex, _targetItem);
}

bool UInventoryWidget::CheckCanEquip()
{
	AEquipItem* target = Cast<AEquipItem>(_targetItem);
	bool result = false;
	switch (target->GetEquipType())
	{
	case EItemType::Helmet:
		if (Helmet->GetItem() == nullptr)
		{
			Helmet->SetItem(_targetItem);
			_targetItem = nullptr;
			result = true;
		}
		else
		{
			_targetItem = Helmet->GetItem();
			Helmet->SetItem(target);
			result = false;
		}
		break;
	case EItemType::UpperArmor:
		if (UpperArmor->GetItem() == nullptr)
		{
			UpperArmor->SetItem(_targetItem);
			_targetItem = nullptr;
			result = true;
		}
		else
		{
			_targetItem = UpperArmor->GetItem();
			UpperArmor->SetItem(target);
			result = false;
		}
		break;
	case EItemType::LowerArmor:
		if (LowerArmor->GetItem() == nullptr)
		{
			LowerArmor->SetItem(_targetItem);
			_targetItem = nullptr;
			result = true;
		}
		else
		{
			_targetItem = LowerArmor->GetItem();
			LowerArmor->SetItem(target);
			result = false;
		}
		break;
	case EItemType::ShoulderArmor:
		if (ShoulderGuard->GetItem() == nullptr)
		{
			ShoulderGuard->SetItem(_targetItem);
			_targetItem = nullptr;
			result = true;
		}
		else
		{
			_targetItem = ShoulderGuard->GetItem();
			ShoulderGuard->SetItem(target);
			result = false;
		}
		break;
	case EItemType::Sword:
		if (Sword->GetItem() == nullptr)
		{
			Sword->SetItem(_targetItem);
			_targetItem = nullptr;
			result = true;
		}
		else
		{
			_targetItem = Sword->GetItem();
			Sword->SetItem(target);
			result = false;
		}
		break;
	case EItemType::Shield:
		if (Shield->GetItem() == nullptr)
		{
			Shield->SetItem(_targetItem);
			_targetItem = nullptr;
			result = true;
		}
		else
		{
			_targetItem = Shield->GetItem();
			Shield->SetItem(target);
			result = false;
		}
		break;
	default:
		break;
	}

	return result;
}

void UInventoryWidget::SetTargetItem(int32 slotIndex)
{
	if (Button_[slotIndex] == nullptr)
		return;

	ABaseItem* item = Button_[slotIndex]->GetItem();
	if (item == nullptr) return;

	_targetItem = item;
	_targetIndex = slotIndex;
	ShowItem();
}

void UInventoryWidget::TargetItem0()
{
	SetTargetItem(0);
}

void UInventoryWidget::TargetItem1()
{
	SetTargetItem(1);
}

void UInventoryWidget::TargetItem2()
{
	SetTargetItem(2);
}

void UInventoryWidget::TargetItem3()
{
	SetTargetItem(3);
}

void UInventoryWidget::TargetItem4()
{
	SetTargetItem(4);
}

void UInventoryWidget::TargetItem5()
{
	SetTargetItem(5);
}

void UInventoryWidget::TargetItem6()
{
	SetTargetItem(6);
}

void UInventoryWidget::TargetItem7()
{
	SetTargetItem(7);
}

void UInventoryWidget::TargetItem8()
{
	SetTargetItem(8);
}

void UInventoryWidget::TargetItem9()
{
	SetTargetItem(9);
}

void UInventoryWidget::TargetItem10()
{
	SetTargetItem(10);
}

void UInventoryWidget::TargetItem11()
{
	SetTargetItem(11);
}
