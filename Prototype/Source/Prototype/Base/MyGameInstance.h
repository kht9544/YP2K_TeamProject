// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers/EffectManager.h"
#include "Managers/SoundManager.h"
#include "Component/StatComponent.h"
#include "../Item/BaseItem.h"
#include "Item/Equip/EquipItem.h"
#include "MyGameInstance.generated.h"

#define GAMEINSTANCE Cast<UMyGameInstance>(GetWorld()->GetGameInstance())
#define UIManager Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()
#define T_DEFAULT Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()->GetDefaultTexture()
#define SoundManager Cast<UMyGameInstance>(GetGameInstance())->GetSoundManager()
#define EffectManager Cast<UMyGameInstance>(GetGameInstance())->GetEffectManager()

UCLASS()
class PROTOTYPE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	void SavePlayerStats(class UStatComponent* StatComponent);
	void LoadPlayerStats(class UStatComponent* StatComponent);

	UPROPERTY()
	TArray<ABaseItem*> SavedItemSlots;

	UPROPERTY()
    TMap<FString,AEquipItem*> SavedEquipSlots;

	void SaveInventoryData(const TArray<ABaseItem*>& ItemSlots, const TMap<FString, AEquipItem*>& EquipSlots);
	void LoadInventoryData(TArray<ABaseItem*>& ItemSlots, TMap<FString, AEquipItem*>& EquipSlots);


	bool GetFirst(){return _firstIn;}
	void SetFirst(bool first){_firstIn = first;}

	bool GetFirst2(){return _firstIn2;}
	void SetFirst2(bool first){_firstIn2 = first;}

public:
	virtual void Init() override;

	UFUNCTION()
	void InitializeManagers();
	
	class AUIManager* GetUIManager() { return _UIManager; }

	FMyStatData* GetStatDataByLevel(int level);
	FMyStatData* GetEpicDataByLevel(int level);
	FMyStatData* GetBossDataByLevel(int level);

	FItemData* GetConsumeItemData(int code);
	FItemData* GetEquipItemData(int code);

	ASoundManager* GetSoundManager() { return _soundManager; }
	AEffectManager* GetEffectManager() { return _effectManager; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AUIManager* _UIManager;

	UPROPERTY()
	UDataTable* _statTable;

	UPROPERTY()
	UDataTable* _EpicstatTable;

	UPROPERTY()
	UDataTable* _BossstatTable;

	UPROPERTY()
	UDataTable* _ConsItemTable;
	UPROPERTY()
	UDataTable* _EquipItemTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ASoundManager* _soundManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AEffectManager* _effectManager;

	UPROPERTY()
	int32 _savedLevel;
	UPROPERTY()
	int32 _savedMaxHp;
	UPROPERTY()
	int32 _savedMaxMp;
	UPROPERTY()
	int32 _savedStr;
	UPROPERTY()
	int32 _savedDex;
	UPROPERTY()
	int32 _savedInt;
	UPROPERTY()
	int32 _savedCurHp;
	UPROPERTY()
	int32 _savedCurMp;
	UPROPERTY()
	int32 _savedExp;
	UPROPERTY()
	bool _firstIn = true;

	UPROPERTY()
	bool _firstIn2 = true;

	

};
