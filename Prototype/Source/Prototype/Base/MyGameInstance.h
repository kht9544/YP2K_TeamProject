// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers/EffectManager.h"
#include "Managers/SoundManager.h"
#include "Component/StatComponent.h"
#include "../Item/BaseItem.h"
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

private:

public:
	virtual void Init() override;
	
	class AUIManager* GetUIManager() { return _UIManager; }

	FMyStatData* GetStatDataByLevel(int level);
	FMyStatData* GetEpicDataByLevel(int level);
	FMyStatData* GetBossDataByLevel(int level);

	FItemData* GetConsumeItemData(int code);
	FItemData* GetEquipItemData(int code);

	ASoundManager* GetSoundManager() { return _soundManager; }
	AEffectManager* GetEffectManager() { return _effectManager; }

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

	UPROPERTY()
	UDataTable* _ConsItemTable;
	UPROPERTY()
	UDataTable* _EquipItemTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ASoundManager* _soundManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AEffectManager* _effectManager;
};
