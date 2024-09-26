// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MyGameInstance.h"
#include "Component/StatComponent.h"
#include "Player/MyPlayerController.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	// 임시 게임인스턴스 아직 구현전이라 임시로 작성 
	//_level = 1; 
	//_maxHp = 100; 
	//_curHp = _maxHp; 
	//_maxMp = 50; 
	//_curMp = _maxMp; 
	//_str = 10; 
	//_dex = 10; 
	//_int = 10; 
	//_bonusPoint = 3;
}




// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...


	

}


//void UStatComponent::SetStat()
//{
//	// 무슨 문제? 
//	if (StatDataTable != nullptr)
//	{
//		TArray<FMyStatData*> AllRows;
//		StatDataTable->GetAllRows(TEXT(""), AllRows);
//
//		if (AllRows.IsValidIndex(_level - 1)) 
//		{
//			const FMyStatData& Data = *AllRows[_level - 1];
//
//		
//			if (&Data != nullptr) 
//			{
//				_maxHp = Data.MaxHP;
//				_curHp = _maxHp;
//				_maxMp = Data.MaxMP;
//				_curMp = _maxMp;
//				_str = Data.STR;
//				_dex = Data.DEX;
//				_int = Data.INT;
//				
//			}
//		}
//	}
//}

// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatComponent::Reset()
{
	_curHp = _maxHp;
}

void UStatComponent::SetLevelInit(int level)
{
	// StatCom에서 스탯들을 인식못해서 현재 0 으로 출력 
	// 실행하고 중단점 잡고 데이터테이블 값은 몇으로 나오는지 실행해볼것
	// 스탯데이터테이블도 다시 만들어보기

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;

	if (myGameInstance)
	{
		Data = myGameInstance->GetStatDataByLevel(level);
		_level = level;
		_maxHp = Data->MaxHP;
		_curHp = 0;
		_maxMp = Data->MaxMP;
		_curMp = 0;
		_str = Data->STR;
		_dex = Data->DEX;
		_int = Data->INT;
		_nextExp = Data->EXP;
		_curExp = 0;
		SetHp(_maxHp);
		SetMp(_maxMp);
		_bonusPoint = Data->BonusPoint;
		_PILevelDelegate.Broadcast(_level);

	}

}


void UStatComponent::SetMaxHp(int32 newMaxHp)
{

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;

	_maxHp = Data->MaxHP;
	_maxHp = FMath::Clamp(newMaxHp, 0, 10000);

}

void UStatComponent::SetMaxMp(int32 newMaxMp)
{

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;


	_maxMp = Data->MaxMP;
	_maxMp = FMath::Clamp(newMaxMp, 0, 10000);

}

void UStatComponent::SetBonusPoint(int32 newBp)
{
	//TArray<FMyStatData*> AllRows;
	//StatDataTable->GetAllRows(TEXT(""), AllRows);

	//	const FMyStatData& Data = *AllRows[_level - 1];
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;

		_bonusPoint = Data->BonusPoint;
		_bonusPoint = FMath::Clamp(newBp, 0, 10);
}

void UStatComponent::SetStr(int32 newstr)
{

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;


	_str = Data->STR;
	_str = FMath::Clamp(newstr, 0, 100);
}

void UStatComponent::SetDex(int32 newdex)
{

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;


	_dex = Data->DEX;
	_dex = FMath::Clamp(newdex, 0, 100);
}

void UStatComponent::SetInt(int32 newint)
{

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;


	_int = Data->INT;
	_int = FMath::Clamp(newint, 0, 100);
}

void UStatComponent::SetHp(int32 hp)
{
	_curHp = hp;
	if (_curHp <= 0)
	{
		_deathDelegate.Broadcast();
		_deathDelegate.Clear();
		_curHp = 0;
	}
	if (_curHp > _maxHp)
	{
		_curHp = _maxHp;
	}

	float ratio = HpRatio();
	_PlHPDelegate.Broadcast(ratio);

}

void UStatComponent::SetMp(int32 mp)
{
	_curMp = mp;
	if (_curMp < 0)
	{
		_curMp = 0;
	}

	if (_curMp > _maxMp)
	{
		_curMp = _maxMp;
	}

	float ratio = _curMp / (float)_maxMp;

	_PlMPDelegate.Broadcast(ratio);
}

int UStatComponent::AddCurHp(int32 amount)
{
	int beforeHp = _curHp;

	int afterHp = beforeHp + amount;
	SetHp(afterHp);

	return afterHp - beforeHp;
}

int UStatComponent::AddCurMp(int32 amount)
{
	int beforeMp = _curMp;

	int afterMp = beforeMp + amount;
	SetMp(afterMp);

	return afterMp - beforeMp;
}

void UStatComponent::AddAttackDamage(float amount)
{
	_attackDamage += amount;
	UE_LOG(LogTemp, Warning, TEXT("Attack Damage: %d"), _attackDamage);
}

void UStatComponent::AddExp(int32 amount)
{
	if (_level == 3)
		return;
	_curExp += amount;

	while (_curExp >= _nextExp)
	{
		_curExp -= _nextExp;
		_level++;
		_nextExp = 100 + (_level * 50); 
		_PILevelDelegate.Broadcast(_level);

		_bonusPoint += 6;

	}
	float ratio = EXpRatio();
	_PlEXPDelegate.Broadcast(ratio);
}



	/*if (StatDataTable != nullptr)
	{
		TArray<FMyStatData*> AllRows;
		StatDataTable->GetAllRows(TEXT(""), AllRows);

		if (AllRows.IsValidIndex(_level - 1))
		{
			const FMyStatData& Data = *AllRows[_level - 1];


			if (&Data != nullptr)
			{
				_maxHp = Data.MaxHP;
				_curHp = _maxHp;
				_maxMp = Data.MaxMP;
				_curMp = _maxMp;
				_str = Data.STR;
				_dex = Data.DEX;
				_int = Data.INT;
				_bonusPoint = Data.BonusPoint;

			}
		}
	}*/




