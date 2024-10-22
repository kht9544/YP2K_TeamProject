// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Elements/IndexedButton.h"
#include "Components/Image.h"

void UIndexedButton::ButtonUpdate()
{
	FSlateBrush imageBrush;

	if (_image != nullptr)
	{
		imageBrush.SetResourceObject(_image);
	}
	//TODO : Why Linking Error??
	FButtonStyle buttonStyle;
	buttonStyle.SetNormal(imageBrush);
	buttonStyle.SetHovered(imageBrush);
	buttonStyle.SetPressed(imageBrush);

	this->SetStyle(buttonStyle);
	
}
