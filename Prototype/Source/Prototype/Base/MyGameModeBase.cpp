// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "../Component/StatComponent.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"


AMyGameModeBase::AMyGameModeBase()
{
    
}

void AMyGameModeBase::BeginPlay()
{
    AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		UStatComponent* StatComponent = player->FindComponentByClass<UStatComponent>();
		if (StatComponent)
		{
			player->_StatCom->SetLevelInit(1);
		}
	}
}

void AMyGameModeBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}
