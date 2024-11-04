// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class ABaseItem;
class UIndexedButton;

DECLARE_MULTICAST_DELEGATE_TwoParams(ItemDropDelegate, int32, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(ItemUseDelegate, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(ItemEquipDelegate, int32);


UCLASS()
class PROTOTYPE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

public:

	void SetItemButtons();
	void SetEquipButtons();
	void SetStats();

	void SetItemImage(int32 slotIndex, ABaseItem* item = nullptr);
	void SetEquipImage(int32 slotIndex, ABaseItem* item = nullptr);
	void UpdateEquip();
	void ShowItem();

	UFUNCTION()
	void DropItem();
	UFUNCTION()
	void UseItem();

	bool CheckCanEquip();

private:
	void SetTargetItem(int32 slotIndex);
	UFUNCTION()
	void TargetItem0();
	UFUNCTION()
	void TargetItem1();
	UFUNCTION()
	void TargetItem2();
	UFUNCTION()
	void TargetItem3();
	UFUNCTION()
	void TargetItem4();
	UFUNCTION()
	void TargetItem5();
	UFUNCTION()
	void TargetItem6();
	UFUNCTION()
	void TargetItem7();
	UFUNCTION()
	void TargetItem8();
	UFUNCTION()
	void TargetItem9();
	UFUNCTION()
	void TargetItem10();
	UFUNCTION()
	void TargetItem11();

public:
	//Delegate
	ItemDropDelegate  ItemDrop;
	ItemUseDelegate   ItemUse;
	ItemEquipDelegate ItemEquip;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (AllowPrivateAccess = "true"))
	FString _defaultText;

	UPROPERTY()
	ABaseItem* _targetItem = nullptr;
	UPROPERTY()
	int32 _targetIndex = -1;

	//UI Elememts
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemSlots;
	UPROPERTY(meta = (BindWidget))
	TArray<UIndexedButton*> Button_;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemTexture;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemDesc;

	UPROPERTY(meta = (BindWidget))
	class UButton* DropBtn;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DropBtnText;
	UPROPERTY(meta = (BindWidget))
	class UButton* UseBtn;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UseBtnText;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* EquipSlots;
	UPROPERTY(meta = (BindWidget))
	UIndexedButton* Helmet;
	UPROPERTY(meta = (BindWidget))
	UIndexedButton* ShoulderGuard;
	UPROPERTY(meta = (BindWidget))
	UIndexedButton* UpperArmor;
	UPROPERTY(meta = (BindWidget))
	UIndexedButton* LowerArmor;
	UPROPERTY(meta = (BindWidget))
	UIndexedButton* Sword;
	UPROPERTY(meta = (BindWidget))
	UIndexedButton* Shield;


	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* StatSlots;
	
};
