// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Component/StatComponent.h"
#include "MyGameInstance.generated.h"

#define UIManager Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()

UCLASS()
class PROTOTYPE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

private:

public:
	void GetItemDataTable();
	virtual void Init() override;
	struct FItemData* GetItemDataByCode(int32 code);

	class AUIManager* GetUIManager() { return _UIManager; }

	FMyStatData* GetStatDataByLevel(int level);
	FMyStatData* GetEpicDataByLevel(int level);
	FMyStatData* GetBossDataByLevel(int level);

	UPROPERTY(BlueprintReadWrite, Category = "Stat")
	int32 _playerLevel;

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SavePlayerStatus(int32 Level);

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void LoadPlayerStatus(int32& Level);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AUIManager* _UIManager;

	UPROPERTY()
	UDataTable* _statTable;

	UPROPERTY()
	UDataTable* _EpicstatTable;

	UPROPERTY()
	UDataTable* _BossstatTable;

};
