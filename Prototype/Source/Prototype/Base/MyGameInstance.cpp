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

}

void UMyGameInstance::Init()
{
	Super::Init();

	FActorSpawnParameters params;
	params.Name = TEXT("UIManager");
	_UIManager = GetWorld()->SpawnActor<AUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	LoadPlayerStatus(_playerLevel);
	auto statData = GetStatDataByLevel(_playerLevel);

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

void UMyGameInstance::SavePlayerStatus(int32 Level)
{
	_playerLevel = Level;

}

void UMyGameInstance::LoadPlayerStatus(int32& Level)
{
	Level = _playerLevel;
}
