// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class ABaseItem;

UCLASS()
class PROTOTYPE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	void SetButtons();

	void SetItemImage(int32 slotIndex, ABaseItem* item);

	void ShowItem();

	void ExchangeEquip(int32 slotIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (AllowPrivateAccess = "true"))
	class UTexture2D* _defaultTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (AllowPrivateAccess = "true"))
	FString _defaultText;

	UPROPERTY()
	ABaseItem* _targetItem;
	UPROPERTY()
	int32 _targetIndex = -1;

	//UI Elememts
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemSlots;
	UPROPERTY(meta = (BindWidget))
	TArray<class UIndexedButton*> Button_;
	UPROPERTY(meta = (BindWidget))
	TArray<class UImage*> Image_;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemTexture;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemDesc;

	UPROPERTY(meta = (BindWidget))
	class UButton* DropBtn;
	UPROPERTY(meta = (BindWidget))
	class UButton* UseBtn;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* EquipSlots;
	UPROPERTY(meta = (BindWidget))
	class UButton* Helmet;
	UPROPERTY(meta = (BindWidget))
	class UButton* ShoulderGuard;
	UPROPERTY(meta = (BindWidget))
	class UButton* UpperArmor;
	UPROPERTY(meta = (BindWidget))
	class UButton* LowerArmor;
	UPROPERTY(meta = (BindWidget))
	class UButton* Sword;
	UPROPERTY(meta = (BindWidget))
	class UButton* Shield;


	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* StatSlots;
	
};
