// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatWidget.h"


#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Player/MyPlayer.h"
#include "Components/TextBlock.h"



void UStatWidget::NativeConstruct()
{
	
	Super::NativeConstruct();

	auto array = SlotGrid->GetAllChildren();

	for (auto widget : array)
	{
		auto btn = Cast<UButton>(widget);
		if (btn)
		{
			_slotBtns.Add(btn);
			_slotBtnText.Add(Cast<UTextBlock>(btn->GetChildAt(0)));
		}
	}

	if (HPUp)
	{
		HPUp->OnClicked.AddDynamic(this, &UStatWidget::HPUpClick);
	}

	if (MPUp)
	{
		MPUp->OnClicked.AddDynamic(this, &UStatWidget::MpUpClick);
	}

	if (STRUp)
	{
		STRUp->OnClicked.AddDynamic(this, &UStatWidget::STRUpClick);

	}
	if (DEXUp)
	{
		DEXUp->OnClicked.AddDynamic(this, &UStatWidget::DEXUpClick);
	}
	if (INTUp)
	{
		INTUp->OnClicked.AddDynamic(this, &UStatWidget::INTUpClick);
	}

	if (HPDown)
	{
		HPDown->OnClicked.AddDynamic(this, &UStatWidget::HPDownClick);
	}
}

void UStatWidget::StatUpdate(StatType type, int amount)
{
	switch (type)
	{
	case StatType::HP:
		// 여기서 각 함수내용들 넣어서 처리
		//  UI 변수 함수 간편화
		break;
	case StatType::MP:
		break;
	case StatType::STR:
		break;
	case StatType::DEX:
		break;
	case StatType::INT:
		break;
	case StatType::CurHP:
		break;
	case StatType::CurMP:
		break;
	default:
		break;
	}
}

void UStatWidget::PlLevelUpdate(int32 Level)
{
	if (PlLevel)
	{
		PlLevel->SetText(FText::AsNumber(Level));
	}
}

void UStatWidget::HPUpdate(int32 HP)
{
	if (HPNum)
	{
		HPNum->SetText(FText::AsNumber(HP));
		
	}
}

void UStatWidget::MPUpdate(int32 MP)
{
	if (MPNum != nullptr)
	{
		MPNum->SetText(FText::AsNumber(MP));
	}
}

void UStatWidget::STRUpdate(int32 STR)
{
	if (STRNum != nullptr)
	{
		STRNum->SetText(FText::AsNumber(STR));
	}
}

void UStatWidget::DEXUpdate(int32 DEX)
{
	if (DEXNum != nullptr)
	{
		DEXNum->SetText(FText::AsNumber(DEX));
	}
}

void UStatWidget::INTUpdate(int32 INT)
{
	if (INTNum != nullptr)
	{
		INTNum->SetText(FText::AsNumber(INT));
	}
}

void UStatWidget::BonusPointUpdate(int32 BonusPoint)
{
	if (BonusNum != nullptr)
	{
		BonusNum->SetText(FText::AsNumber(BonusPoint));
	}
}


void UStatWidget::UpdateStatDisplay()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->_StatCom)
	{
		HPUpdate(player->_StatCom->GetMaxHp());
		MPUpdate(player->_StatCom->GetMaxMp());
		STRUpdate(player->_StatCom->GetStr());
		DEXUpdate(player->_StatCom->GetDex());
		INTUpdate(player->_StatCom->GetInt());
		
		BonusPointUpdate(player->_StatCom->GetBonusPoint());
		PlLevelUpdate(player->_StatCom->GetLevel());

		// 스탯 Log
		UE_LOG(LogTemp, Warning, TEXT("HP: %d, MP: %d, STR: %d, DEX: %d, INT: %d, EXP: %d, BonusPoint: %d"),
			player->_StatCom->GetMaxHp(),
			player->_StatCom->GetMaxMp(),
			player->_StatCom->GetStr(),
			player->_StatCom->GetDex(),
			player->_StatCom->GetInt(),
			player->_StatCom->GetExp(),
			player->_StatCom->GetBonusPoint());

	}
}

void UStatWidget::HPDownClick()
{
	
	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->_StatCom)
	{
		int32 currentHp = player->_StatCom->GetMaxHp();
		int32 baseHp = player->_StatCom->GetBaseStat(StatType::HP);  // 기준 HP 가져오기
		int32 bonusPoints = player->_StatCom->GetBonusPoint();

		if (currentHp > baseHp) 
		{
			player->_StatCom->SetMaxHp(currentHp - 100);
			player->_StatCom->SetBonusPoint(bonusPoints + 1);
		}
		UpdateStatDisplay();
	}
}


void UStatWidget::HPUpClick()
{

	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->_StatCom)
	{
		int32 plMaxHp = player->_StatCom->GetMaxHp();
		int32 BonusPoints = player->_StatCom->GetBonusPoint();

		if (BonusPoints > 0)
		{
			player->_StatCom->SetMaxHp(plMaxHp + 100);
			player->_StatCom->SetBonusPoint(BonusPoints - 1);

		}
		UpdateStatDisplay();


	}
}

void UStatWidget::MpUpClick()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->_StatCom)
	{
		int32 plMaxMp = player->_StatCom->GetMaxMp();
		int32 BonusPoints = player->_StatCom->GetBonusPoint();

		if (BonusPoints > 0)
		{
			player->_StatCom->SetMaxMp(plMaxMp + 10);
			player->_StatCom->SetBonusPoint(BonusPoints - 1);
		}
		UpdateStatDisplay();


	}
}


void UStatWidget::STRUpClick()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());
	UE_LOG(LogTemp, Error, TEXT("click Errow"));

	if (player && player->_StatCom)
	{
		int32 plStr = player->_StatCom->GetStr();
		int32 BonusPoints = player->_StatCom->GetBonusPoint();

		if (BonusPoints > 0)
		{
			player->_StatCom->SetStr(plStr + 1);
			player->_StatCom->SetBonusPoint(BonusPoints - 1);
		}
		// 클릭마다 ui 업데이트
		UpdateStatDisplay();
		//UpdateStatDisplay();
		UE_LOG(LogTemp, Error, TEXT("test Errow"));
	}
}

void UStatWidget::DEXUpClick()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());
	UE_LOG(LogTemp, Error, TEXT("click Errow"));

	if (player && player->_StatCom)
	{
		int32 StatDex = player->_StatCom->GetDex();
		int32 StatBonusPoints = player->_StatCom->GetBonusPoint();

		if (StatBonusPoints > 0)
		{
			player->_StatCom->SetDex(StatDex + 1);
			player->_StatCom->SetBonusPoint(StatBonusPoints - 1);
		}
		// 클릭마다 ui 업데이트
		UpdateStatDisplay();
		//UpdateStatDisplay();
		UE_LOG(LogTemp, Error, TEXT("test Errow"));
	}
}

void UStatWidget::INTUpClick()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());
	UE_LOG(LogTemp, Error, TEXT("click Errow"));

	if (player && player->_StatCom)
	{
		int32 StatInt = player->_StatCom->GetInt();
		int32 StatBonusPoints = player->_StatCom->GetBonusPoint();

		if (StatBonusPoints > 0)
		{
			player->_StatCom->SetInt(StatInt + 1);
			player->_StatCom->SetBonusPoint(StatBonusPoints - 1);
		}
		// 클릭마다 ui 업데이트
		UpdateStatDisplay();
		//UpdateStatDisplay();
		UE_LOG(LogTemp, Error, TEXT("test Errow"));
	}
}
