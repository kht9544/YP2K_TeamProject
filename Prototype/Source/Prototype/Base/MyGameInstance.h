// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

#define UIManager Cast<UMyGameInstance>(GetWorld()->GetGameInstance()->GetUIManager())

UCLASS()
class PROTOTYPE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

private:
	virtual void Init() override;
	void GetItemDataTable();

public:
	struct FItemData* GetItemDataByCode(int32 code);

	class AUIManager* GetUIManager() { return _UIManager; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AUIManager* _UIManager;

};
