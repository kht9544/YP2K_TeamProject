// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MyGameInstance.h"

#include "Base/Managers/UIManager.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> StatData
	(TEXT("/Script/Engine.DataTable'/Game/Data/StatDataTable.StatDataTable'"));

	if (StatData.Succeeded())
	{
		_statTable = StatData.Object;

	}

	// 현재 에픽 스탯데이터테이블 까지완
	static ConstructorHelpers::FObjectFinder<UDataTable> EpicStatData
	(TEXT("/Script/Engine.DataTable'/Game/Data/EpicMonsterDataTable.EpicMonsterDataTable'"));

	if (EpicStatData.Succeeded())
	{
		_EpicstatTable = EpicStatData.Object;

	}

}

void UMyGameInstance::Init()
{
	Super::Init();

	FActorSpawnParameters params;
	params.Name = TEXT("UIManager");
	_UIManager = GetWorld()->SpawnActor<AUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	LoadPlayerStatus(_playerLevel);
	auto statData = GetStatDataByLevel(_playerLevel);
	auto EpicData = GetEpicDataByLevel(1);
}

void UMyGameInstance::GetItemDataTable()
{
}

FItemData* UMyGameInstance::GetItemDataByCode(int32 code)
{
	return nullptr;
}

FMyStatData* UMyGameInstance::GetStatDataByLevel(int level)
{
	auto statData = _statTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return statData;
}

FMyStatData* UMyGameInstance::GetEpicDataByLevel(int level)
{
	auto EpicStatData = _EpicstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return EpicStatData;
}

void UMyGameInstance::SavePlayerStatus(int32 Level)
{
	_playerLevel = Level;

}

void UMyGameInstance::LoadPlayerStatus(int32& Level)
{
	Level = _playerLevel;
}
