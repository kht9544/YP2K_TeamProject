// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "IndexedButton.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UIndexedButton : public UButton
{
	GENERATED_BODY()
	
public:
	int32 GetIndex() { return _index; }
	void SetIndex(int32 index) { _index = index; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 _index;
};
