// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Elements/IndexedButton.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "Styling/SlateTypes.h"
#include "Components/Image.h"

void UIndexedButton::ButtonUpdate()
{
	FSlateBrush imageBrush;

	if (_image != nullptr)
	{
		imageBrush.SetResourceObject(_image);
	}
	else
	{
		imageBrush.SetResourceObject(T_DEFAULT);
	}
	//TODO : Image is SO SMALL
	FButtonStyle btnStyle;
	btnStyle.SetNormal(imageBrush);
	btnStyle.SetHovered(imageBrush);
	btnStyle.SetPressed(imageBrush);
	
	this->SetStyle(btnStyle);
}
