// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Boss1Widget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"


void UBoss1Widget::UpdateBossHPBar(float Ratio)
{
    BossHPBar->SetPercent(Ratio);
}

void UBoss1Widget::UpdateHPBarColor(int32 DestroyCount)
{
    if (BossHPBar)
	{
		FLinearColor NewColor = FLinearColor::Gray;
		UE_LOG(LogTemp, Warning, TEXT("updatehp"));
		switch (DestroyCount)
		{
		case 1:
			NewColor = FLinearColor(0.7f, 0.3f, 0.3f);
			break;
		case 2:
			NewColor = FLinearColor(0.8f, 0.2f, 0.2f);
			break;
		case 3:
			NewColor = FLinearColor(0.9f, 0.1f, 0.1f);
			break;
		case 4:
			NewColor = FLinearColor::Red;
			break;
		default:
			break;
		}

		BossHPBar->SetFillColorAndOpacity(NewColor);
	}
}

void UBoss1Widget::UpdateObstacleIcons(int32 DestroyCount)
{
    if (ObstacleIcons.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("updateicon"));
		for (int32 i = 0; i < ObstacleIcons.Num(); i++)
		{
			if (i < DestroyCount)
			{
				ObstacleIcons[i]->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				ObstacleIcons[i]->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}
