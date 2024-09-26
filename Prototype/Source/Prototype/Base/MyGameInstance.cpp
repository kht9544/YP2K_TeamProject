// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MyGameInstance.h"

#include "Base/Managers/UIManager.h"

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	FActorSpawnParameters params;
	params.Name = TEXT("UIManager");
	_UIManager = GetWorld()->SpawnActor<AUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);
}

void UMyGameInstance::GetItemDataTable()
{
}

FItemData* UMyGameInstance::GetItemDataByCode(int32 code)
{
	return nullptr;
}
